#include <stdio.h>
#include "stdlib.h"
#include <tchar.h>
//#include <string>
#include <windows.h>
extern "C" {

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	printf("%d\n",123123);
	b=2;
    return TRUE;
}



};
