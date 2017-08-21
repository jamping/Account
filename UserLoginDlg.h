#if !defined(AFX_USERLOGINDLG_H__E7829D79_F350_4C81_9088_0AB5D8D570B9__INCLUDED_)
#define AFX_USERLOGINDLG_H__E7829D79_F350_4C81_9088_0AB5D8D570B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserLoginDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserLoginDlg dialog

class CUserLoginDlg : public CDialog
{
// Construction
public:
	CUserLoginDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUserLoginDlg)
	enum { IDD = IDD_LOGIN };
	CComboBox	m_ctlUserName;
	CBCGPButton	m_btnLogin;
	CString	m_strPassWord;
	CString	m_strUserName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserLoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserLoginDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnLogin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERLOGINDLG_H__E7829D79_F350_4C81_9088_0AB5D8D570B9__INCLUDED_)
