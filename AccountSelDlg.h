#if !defined(AFX_ACCOUNTSELDLG_H__9FC5FF7C_FD0C_4507_85D9_DE8EA3B65735__INCLUDED_)
#define AFX_ACCOUNTSELDLG_H__9FC5FF7C_FD0C_4507_85D9_DE8EA3B65735__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AccountSelDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAccountSelDlg dialog

class CAccountSelDlg : public CDialog
{
// Construction
public:
	CAccountSelDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAccountSelDlg)
	enum { IDD = IDD_ACCOUNT_SEL };
	CBCGPButton	m_btn3;
	CBCGPButton	m_btn2;
	CBCGPButton	m_btn1;
	//}}AFX_DATA

    UINT GetAccountType() { return m_nType ;}
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccountSelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
     UINT   m_nType;
	// Generated message map functions
	//{{AFX_MSG(CAccountSelDlg)
	afx_msg void OnButtonAccount();
	afx_msg void OnButtonAccount2();
	afx_msg void OnButtonAccount3();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCOUNTSELDLG_H__9FC5FF7C_FD0C_4507_85D9_DE8EA3B65735__INCLUDED_)
