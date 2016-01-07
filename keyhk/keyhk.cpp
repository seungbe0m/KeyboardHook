// keyhk.cpp : DLL ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <windows.h>
#include <strsafe.h>
#include "keyhk.h"

#pragma data_seg("Shared")
HWND g_targetWnd = NULL;
UINT g_callbackMsg = 0;
#pragma data_seg()

#pragma comment(linker, "/SECTION:Shared,RWS")

HHOOK       g_hHook = NULL;
HINSTANCE   g_hInst = NULL;


BOOL WINAPI
DllMain(HINSTANCE hInst, DWORD reason, LPVOID /* reserved */)
{
    g_hInst = hInst;

	// ������ ������ ���� �ʴ´�.
    if(reason == DLL_PROCESS_ATTACH)
        DisableThreadLibraryCalls(hInst);

    return TRUE;
}

// Ű���� ��ŷ ���ν���
LRESULT CALLBACK
KeyHook(int code, WPARAM w, LPARAM l)
{
	if(code >= 0)
	{
		TCHAR buf[80];

        StringCbPrintf(buf, sizeof(buf), TEXT("%c"), w);
		OutputDebugString(buf);
	}

    return CallNextHookEx(NULL, code, w, l);
}

LRESULT CALLBACK
KeyHookEx(int code, WPARAM w, LPARAM l)
{
	if(code >= 0)
	{
		TCHAR buf[80];

        StringCbPrintf(buf, sizeof(buf), TEXT("W=%08X(%c) L=%08X"), w, w, l);
		OutputDebugString(buf);

		if(w == 'W')
			return TRUE;
	}

    return CallNextHookEx(NULL, code, w, l);
}

LRESULT CALLBACK
KeyHookMsg(int code, WPARAM w, LPARAM l)
{
	if(code >= 0 && IsWindow(g_targetWnd))
	{
		PKEYINFO keyInfo = (PKEYINFO) &l;

		if(!keyInfo->extended && !keyInfo->alt && !keyInfo->notPressed)
		{
			BYTE keyState[256];
			WORD ch=0;

			GetKeyboardState(keyState);
			keyState[VK_CONTROL] = 0;
			if(ToAscii((UINT) w, keyInfo->scanCode, keyState, &ch, 0) == 1)
			{

				SendMessageTimeout(	g_targetWnd,
									g_callbackMsg, 
									ch, 
									l, 
									SMTO_BLOCK|SMTO_ABORTIFHUNG, 
									50, 
									NULL	);
			}
		}
	}

    return CallNextHookEx(NULL, code, w, l);
}

// �� ���ν��� ��ġ
KEYHK_API BOOL WINAPI
InstallHook()
{
    BOOL ret = FALSE;

    if(!g_hHook)
    {
        g_hHook = SetWindowsHookEx(WH_KEYBOARD, KeyHookMsg, g_hInst, 0);
        if(g_hHook)
            ret = TRUE;
    }

    return ret;
}

// �� ���ν��� ����
KEYHK_API BOOL WINAPI
UninstallHook()
{
    BOOL ret = FALSE;

    if(g_hHook)
    {
        ret = UnhookWindowsHookEx(g_hHook);

        if(ret)
            g_hHook = NULL;
    }

	return ret;
}

// �޽��� ���� ������ ����
KEYHK_API void WINAPI
SetTargetWnd(HWND wnd, UINT msg)
{
	g_targetWnd = wnd;
	g_callbackMsg = msg;
}