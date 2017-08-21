// AccountDlg.h : header file
//

#if !defined(AFX_ACCOUNTDLG_H__E0928FD9_2C57_4E73_850F_B95B6B28C1A3__INCLUDED_)
#define AFX_ACCOUNTDLG_H__E0928FD9_2C57_4E73_850F_B95B6B28C1A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UserLoginDlg.h"
#include "InOutDlg.h"
#include "ReportDlg.h"
#include "UserAccountDlg.h"
#include "AccountLogDlg.h"
#include "SettingDlg.h"
#include "DataManageDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CAccountDlg dialog

class CAccountDlg : public CDialog
{
// Construction
public:
	friend class CAccountInfoDlg;

	CAccountDlg(CWnd* pParent = NULL);	// standard constructor

	void Init(UINT nValue = 0 );
    
	CBCGPTabWnd	m_wndTab;
// Dialog Data
	//{{AFX_DATA(CAccountDlg)
	enum { IDD = IDD_ACCOUNT_DIALOG };
	CBCGPButton	m_btnPrevDate;
	CBCGPButton	m_btnNextDate;
	CBCGPButton	m_btnOutcome;
	CBCGPButton	m_btnIncome;
	CBCGPButton	m_btnBanlance;
	CBCGPButton	m_btnBackup;
	CBCGPButton	m_btnAccountScope;
	CStatic	m_tabLoc;
	CString	m_strCurUser;
	COleDateTime	m_time;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccountDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	HICON m_hIcon;
    
	CUserLoginDlg  m_dlgLogin;
	CAccountLogDlg  m_dlgAccountLog;
	CInOutDlg  m_dlgInOut;
	CReportDlg  m_dlgReport;
	CUserAccountDlg  m_dlgUserAccount;
	CSettingDlg   m_dlgSetting;
	CDataManageDlg m_dlgDataManage;

	// Generated message map functions
	//{{AFX_MSG(CAccountDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPrevDate();
	afx_msg void OnNextDate();
	afx_msg void OnAccountScope();
	afx_msg void OnIncome();
	afx_msg void OnOutcome();
	afx_msg void OnBanlance();
	afx_msg void OnBackup();
	afx_msg void OnDatetimechangeSelDate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClose();
	//}}AFX_MSG
	afx_msg void OnUpdateInfo();
	afx_msg void OnUpdateIncome(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOutcome(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBalance(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCOUNTDLG_H__E0928FD9_2C57_4E73_850F_B95B6B28C1A3__INCLUDED_)
