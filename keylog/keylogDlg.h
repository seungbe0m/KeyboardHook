// keylogDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CkeylogDlg ��ȭ ����
class CkeylogDlg : public CDialog
{
// ����
public:
	CkeylogDlg(CWnd* pParent = NULL);	// ǥ�� ������

// ��ȭ ���� ������
	enum { IDD = IDD_KEYLOG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ����


// ����
protected:
	HICON m_hIcon;

	// �޽��� �� �Լ��� �����߽��ϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedHook();
	afx_msg void OnBnClickedUnhook();
	afx_msg LRESULT OnKeyMsg(WPARAM w, LPARAM l);
	CEdit m_edtKeyLog;
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedChkAlwaysontop();
	CButton m_chkAlwaysTop;
	afx_msg void OnClose();
};
