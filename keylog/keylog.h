// keylog.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ


// CkeylogApp:
// �� Ŭ������ ������ ���ؼ��� keylog.cpp�� �����Ͻʽÿ�.
//

class CkeylogApp : public CWinApp
{
public:
	CkeylogApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CkeylogApp theApp;
