// keylogDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "keylog.h"
#include "keylogDlg.h"

#include "../keyhk/keyhk.h"
#include ".\keylogdlg.h"

#ifdef _DEBUG
#pragma comment(lib, "../bin/debug/keyhk.lib")
#else
#pragma comment(lib, "../bin/release/keyhk.lib")
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static const UINT WM_KEYMSG = WM_USER+219;

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원

// 구현
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CkeylogDlg 대화 상자



CkeylogDlg::CkeylogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CkeylogDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CkeylogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LOG, m_edtKeyLog);
	DDX_Control(pDX, IDC_CHK_ALWAYSONTOP, m_chkAlwaysTop);
}

BEGIN_MESSAGE_MAP(CkeylogDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_HOOK, OnBnClickedHook)
	ON_BN_CLICKED(IDC_UNHOOK, OnBnClickedUnhook)
	ON_MESSAGE(WM_KEYMSG, OnKeyMsg)
	ON_BN_CLICKED(IDC_CLEAR, OnBnClickedClear)
	ON_BN_CLICKED(IDC_CHK_ALWAYSONTOP, OnBnClickedChkAlwaysontop)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CkeylogDlg 메시지 처리기

BOOL CkeylogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	// 프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	return TRUE;  // 컨트롤에 대한 포커스를 설정하지 않을 경우 TRUE를 반환합니다.
}

void CkeylogDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면 
// 아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
// 프레임워크에서 이 작업을 자동으로 수행합니다.

void CkeylogDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다. 
HCURSOR CkeylogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CkeylogDlg::OnBnClickedHook()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(InstallHook())
	{
		SetTargetWnd(GetSafeHwnd(), WM_KEYMSG);
		AfxMessageBox("키보드 모니터링을 시작합니다.");
	}
}

void CkeylogDlg::OnBnClickedUnhook()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(UninstallHook())
		AfxMessageBox("키보드 모니터링을 종료합니다.");
}

LRESULT CkeylogDlg::OnKeyMsg(WPARAM w, LPARAM l)
{
	CString buf;
	PKEYINFO keyInfo = (PKEYINFO) &l;

	for(unsigned i=0; i<keyInfo->repeatCnt; ++i)
	{
		switch(w)
		{
		case VK_BACK:
			buf += "<BS>";
			break;

		case VK_SPACE:
			buf += "<SP>";
			break;

		case VK_TAB:
			buf += "<TAB>";
			break;

		default:
			buf += (TCHAR) w;
			break;
		}
	}
	
	int len = m_edtKeyLog.GetWindowTextLength();
	m_edtKeyLog.SetSel(len, len);
	m_edtKeyLog.ReplaceSel(buf);

	return 0;
}

void CkeylogDlg::OnBnClickedClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_edtKeyLog.SetWindowText("");
}

void CkeylogDlg::OnBnClickedChkAlwaysontop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_chkAlwaysTop.GetCheck() == BST_CHECKED)
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	else
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
}

void CkeylogDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	UninstallHook();

	CDialog::OnClose();
}



