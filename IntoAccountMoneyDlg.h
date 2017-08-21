#if !defined(AFX_INTOACCOUNTMONEYDLG_H__9B7829E0_4592_4408_B90A_708F226C263C__INCLUDED_)
#define AFX_INTOACCOUNTMONEYDLG_H__9B7829E0_4592_4408_B90A_708F226C263C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IntoAccountMoneyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIntoAccountMoneyDlg dialog

class CIntoAccountMoneyDlg : public CDialog
{
// Construction
public:
	CIntoAccountMoneyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIntoAccountMoneyDlg)
	enum { IDD = IDD_INTO_ACCOUNT };
	CBCGPButton	m_btnOk;
	CBCGPButton	m_btnCancel;
	CBCGPMaskEdit	m_editMoney;
	double	m_dwMoney;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIntoAccountMoneyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIntoAccountMoneyDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTOACCOUNTMONEYDLG_H__9B7829E0_4592_4408_B90A_708F226C263C__INCLUDED_)
