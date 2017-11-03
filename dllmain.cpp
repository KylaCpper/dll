#include <iostream>
#include <Windows.h>
using namespace std;

typedef int(*dllfun)(int,int);
int main()
{
	int a;
	int *b;
	b=0xbfebd5c0;
	HMODULE hDLL = LoadLibrary("dllTest");//加载dll，将dll放在该工程根路径即可
	if(hDLL != NULL)
	{
		dllfun fp;
		fp = (dllfun)(GetProcAddress(hDLL,"Sum"));//获取导入到应用程序中的函数指针，根据方法名取得
		//or
		//FUNA fp = FUNA(GetProcAddress(hDLL,MAKEINTRESOURCE(1)));//根据直接使用DLL中函数出现的顺序号
		while(1)
		{

			cin>>a;

			if(a==5)
			{
				goto end;
			}
			if(fp != NULL)
			{
				
				cout<<fp(1,2);
				cout<<*b;
			}
			else
			{
				cout<<"false"<<endl;
			}
		}
		end:
		FreeLibrary(hDLL);
	}
	else
	{
		cout<<"Cannot Find dll"<<endl;
	}
	return 1;
}