// hkldr.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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

	// DLL�� �ε��Ѵ�.
	inst = LoadLibrary(argv[1]);
	if(inst == NULL)
		goto $cleanup;

	// DLL���� ��ŷ �Լ��� ã�´�.
	FInstallHook fnInstallHook = (FInstallHook) GetProcAddress(inst, TEXT("InstallHook"));
	FUninstallHook fnUninstallHook = (FUninstallHook) GetProcAddress(inst, TEXT("UninstallHook"));
	if(fnInstallHook == NULL || fnUninstallHook == NULL)
		goto $cleanup;

	// ��ŷ�� �Ѵ�.
	if(fnInstallHook())
	{
		printf("press enter key to uninstall hook\n");
		fflush(stdout);
		getchar();

		// ������� �Է��� ���� ��� ��ŷ�� �����Ѵ�.
		fnUninstallHook();
	}

$cleanup:
	// ���̺귯���� �����Ѵ�.
	if(inst)
		FreeLibrary(inst);

	return 0;
}

