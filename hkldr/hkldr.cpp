// hkldr.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <windows.h>

typedef BOOL (WINAPI *FInstallHook)();
typedef BOOL (WINAPI *FUninstallHook)();

int _tmain(int argc, _TCHAR* argv[])
{
	HINSTANCE inst = NULL;

	if(argc < 2)
		goto $cleanup;

	// DLL을 로드한다.
	inst = LoadLibrary(argv[1]);
	if(inst == NULL)
		goto $cleanup;

	// DLL에서 후킹 함수를 찾는다.
	FInstallHook fnInstallHook = (FInstallHook) GetProcAddress(inst, TEXT("InstallHook"));
	FUninstallHook fnUninstallHook = (FUninstallHook) GetProcAddress(inst, TEXT("UninstallHook"));
	if(fnInstallHook == NULL || fnUninstallHook == NULL)
		goto $cleanup;

	// 후킹을 한다.
	if(fnInstallHook())
	{
		printf("press enter key to uninstall hook\n");
		fflush(stdout);
		getchar();

		// 사용자의 입력이 들어온 경우 후킹을 종료한다.
		fnUninstallHook();
	}

$cleanup:
	// 라이브러리를 해제한다.
	if(inst)
		FreeLibrary(inst);

	return 0;
}

