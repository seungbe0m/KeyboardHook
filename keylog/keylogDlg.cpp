// keylogDlg.cpp : ���� ����
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

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� ������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ����

// ����
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


// CkeylogDlg ��ȭ ����



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


// CkeylogDlg �޽��� ó����

BOOL CkeylogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	// �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸����� 
// �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
// �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CkeylogDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�. 
HCURSOR CkeylogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CkeylogDlg::OnBnClickedHook()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(InstallHook())
	{
		SetTargetWnd(GetSafeHwnd(), WM_KEYMSG);
		AfxMessageBox("Ű���� ����͸��� �����մϴ�.");
	}
}

void CkeylogDlg::OnBnClickedUnhook()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(UninstallHook())
		AfxMessageBox("Ű���� ����͸��� �����մϴ�.");
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_edtKeyLog.SetWindowText("");
}

void CkeylogDlg::OnBnClickedChkAlwaysontop()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_chkAlwaysTop.GetCheck() == BST_CHECKED)
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	else
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
}

void CkeylogDlg::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	UninstallHook();

	CDialog::OnClose();
}



