#if !defined(AFX_ACCOUNTINFODLG_H__BD499C5A_E66E_40FF_B867_E971FF42B9C4__INCLUDED_)
#define AFX_ACCOUNTINFODLG_H__BD499C5A_E66E_40FF_B867_E971FF42B9C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AccountInfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAccountInfoDlg dialog

class CAccountInfoDlg : public CDialog
{
// Construction
public:
	CAccountInfoDlg(CAccount *pAccount,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAccountInfoDlg)
	enum { IDD = IDD_ACCOUNT };
	CBCGPButton	m_btnModify;
	CBCGPButton	m_btnCancel;
	CBCGPButton	m_btnMonth;
	CBCGPButton	m_btnOutcome;
	CBCGPButton	m_btnIncome;
	CBCGPButton	m_btnBalance;
	CString	m_strAccountLeft;
	CString	m_strAccountName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccountInfoDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    CAccount * m_pAccount;
	// Generated message map functions
	//{{AFX_MSG(CAccountInfoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBalance();
	afx_msg void OnIncome();
	afx_msg void OnMonth();
	afx_msg void OnOutcome();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnModifyAccount();
	//}}AFX_MSG
	afx_msg void OnUpdateBalance(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCOUNTINFODLG_H__BD499C5A_E66E_40FF_B867_E971FF42B9C4__INCLUDED_)
