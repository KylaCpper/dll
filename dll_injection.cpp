#include <stdio.h>
#include <windows.h>
LPVOID p2;
typedef int(*dllfun)(int,int);
//如果某个函数名代表的地址指向jmp 函数代码，可以将函数传入getFuncAddr,得到函数真正的地址，该函数只在x86上有效
LPVOID getFuncAddr(char* fun)
{
    return LPVOID(fun + *(DWORD*)(fun + 1)+5);
}
int main(int argc,char** argv)
{

    if (argc < 2)
    {
        printf("requir pid\n");
        return 0;
    }
    DWORD pid = 43116;
    sscanf(argv[1], "%d", &pid);//从命令行参数中pid
    
    //打开进程
    HANDLE procTorej=OpenProcess(PROCESS_ALL_ACCESS, false, pid);
    if (procTorej == NULL)
    {
        printf("%d\n", GetLastError());
        return 0;
    }
    printf("Open success\n", GetLastError());
    //在目标进程的地址空间中申请一块内存
    p2 = VirtualAllocEx(procTorej, NULL, 0x2000, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (p2 == NULL)
    {
        printf("VirtualAllocEx 2::%d\n", GetLastError());
        return 0;
    }
    printf("%p\n",p2);
    SIZE_T num = 0;
    //将要注入的动态库名称写入目标进程
    if (WriteProcessMemory(procTorej, p2, "dllTest1.dll", 13, &num) == 0)
    {
        printf("WriteProcessMemory::%d\n", GetLastError());
        return 0;
    }
    printf("%p\n", p2);
    //起一个远程线程加载目标动态库
    //LoadLibraryA 为什么有用，貌似某些系统库总是被映射在每个进程地址空间中的同意位置
    HANDLE hthread=CreateRemoteThread(procTorej, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryA,p2, NULL, NULL);
    if (hthread==NULL)
    {
        printf("CreateRemoteThread::%d\n", GetLastError());
        return 0;
    }
    return 0;
}