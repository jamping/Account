#if !defined(AFX_ACCOUNTMANAGEDLG_H__5CEB710F_A340_4186_A6CA_2B8CE13CF3BD__INCLUDED_)
#define AFX_ACCOUNTMANAGEDLG_H__5CEB710F_A340_4186_A6CA_2B8CE13CF3BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AccountManageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAccountManageDlg dialog

class CAccountManageDlg : public CDialog
{
// Construction
public:
	CAccountManageDlg(CAccount* pAccount,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAccountManageDlg)
	enum { IDD = IDD_ACCOUNT_MANAGE };
	CString	m_strAccountName;
	double	m_dwAccountBase;
	int		m_nAccountType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccountManageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CAccount*   m_pAccount;
	// Generated message map functions
	//{{AFX_MSG(CAccountManageDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCOUNTMANAGEDLG_H__5CEB710F_A340_4186_A6CA_2B8CE13CF3BD__INCLUDED_)
