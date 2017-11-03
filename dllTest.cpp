extern "C" {

	_declspec(dllexport) int Sum(int a,int b);//加法函数。

	_declspec(dllexport) int Sum(int a,int b)
	{
		return a+b;
	}

	BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved  )
	{
		printf("%d",11111);

	    return TRUE;
	}

}
