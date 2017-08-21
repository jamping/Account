#if !defined(AFX_ACCOUNTBUTTON_H__6ABE5800_AB3F_4E6A_A1D0_8980814FF51E__INCLUDED_)
#define AFX_ACCOUNTBUTTON_H__6ABE5800_AB3F_4E6A_A1D0_8980814FF51E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AccountButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAccountButton window
#define IDC_USER_BUTTON_ID  6000

#define  CButton CBCGPButton

class CAccountButton : public CButton
{
// Construction
public:
	CAccountButton();
    
	BOOL Create(const CRect& rect,CWnd * pParent,UINT nID);
	void SetAccount(CAccount* pAccount) { m_pAccount = pAccount; }
// Attributes
private:
     CAccount*   m_pAccount;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccountButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAccountButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAccountButton)
	afx_msg void OnClicked();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCOUNTBUTTON_H__6ABE5800_AB3F_4E6A_A1D0_8980814FF51E__INCLUDED_)
