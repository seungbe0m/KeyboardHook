// keylogDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


// CkeylogDlg 대화 상자
class CkeylogDlg : public CDialog
{
// 생성
public:
	CkeylogDlg(CWnd* pParent = NULL);	// 표준 생성자

// 대화 상자 데이터
	enum { IDD = IDD_KEYLOG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원


// 구현
protected:
	HICON m_hIcon;

	// 메시지 맵 함수를 생성했습니다.
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
