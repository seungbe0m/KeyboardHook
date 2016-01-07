// keyhk.cpp : DLL 응용 프로그램에 대한 진입점을 정의합니다.
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

	// 쓰레드 통지는 받지 않는다.
    if(reason == DLL_PROCESS_ATTACH)
        DisableThreadLibraryCalls(hInst);

    return TRUE;
}

// 키보드 후킹 프로시저
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

// 훅 프로시저 설치
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

// 훅 프로시저 제거
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

// 메시지 받을 윈도우 설정
KEYHK_API void WINAPI
SetTargetWnd(HWND wnd, UINT msg)
{
	g_targetWnd = wnd;
	g_callbackMsg = msg;
}