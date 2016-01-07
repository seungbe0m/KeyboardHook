#pragma once

#ifdef KEYHK_EXPORTS
#define KEYHK_API extern "C" __declspec(dllexport) 
#else
#define KEYHK_API extern "C" __declspec(dllimport)
#endif

typedef struct _KEYINFO
{
	unsigned	repeatCnt:16;			// �ݺ� Ƚ��
	unsigned	scanCode:8;				// ��ĵ �ڵ�
	unsigned	extended:1;				// Ȯ�� Ű
	unsigned	reserved:4;				// �����
	unsigned	alt:1;					// Alt
	unsigned	prevPressed:1;			// ���� Ű ����
	unsigned	notPressed:1;			// ���� Ű ����
} KEYINFO, *PKEYINFO;


/*--
	���� �����Ѵ�.

	�Ķ����
		- ����.

	����
		- ���� �� TRUE, ���� �� FALSE.
--*/
KEYHK_API BOOL WINAPI
InstallHook();

/*--
	���� �����Ѵ�..

	�Ķ����
		- ����.

	����
		- ���� �� TRUE, ���� �� FALSE.
--*/
KEYHK_API BOOL WINAPI
UninstallHook();

/*--
	�޽��� ���� ������ �ڵ��� �����Ѵ�.

	�Ķ����
		wnd - [�Է�] ������ �ڵ�
		msg - [�Է�] �޽��� ��ȣ

	����
		- ����.
--*/
KEYHK_API void WINAPI
SetTargetWnd(HWND wnd, UINT msg);