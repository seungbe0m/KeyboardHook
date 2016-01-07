#pragma once

#ifdef KEYHK_EXPORTS
#define KEYHK_API extern "C" __declspec(dllexport) 
#else
#define KEYHK_API extern "C" __declspec(dllimport)
#endif

typedef struct _KEYINFO
{
	unsigned	repeatCnt:16;			// 반복 횟수
	unsigned	scanCode:8;				// 스캔 코드
	unsigned	extended:1;				// 확장 키
	unsigned	reserved:4;				// 예약됨
	unsigned	alt:1;					// Alt
	unsigned	prevPressed:1;			// 이전 키 상태
	unsigned	notPressed:1;			// 현재 키 상태
} KEYINFO, *PKEYINFO;


/*--
	훅을 설정한다.

	파라미터
		- 없음.

	리턴
		- 성공 시 TRUE, 실패 시 FALSE.
--*/
KEYHK_API BOOL WINAPI
InstallHook();

/*--
	훅을 해제한다..

	파라미터
		- 없음.

	리턴
		- 성공 시 TRUE, 실패 시 FALSE.
--*/
KEYHK_API BOOL WINAPI
UninstallHook();

/*--
	메시지 받을 윈도우 핸들을 설정한다.

	파라미터
		wnd - [입력] 윈도우 핸들
		msg - [입력] 메시지 번호

	리턴
		- 없음.
--*/
KEYHK_API void WINAPI
SetTargetWnd(HWND wnd, UINT msg);