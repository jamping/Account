#if !defined(AFX_DATAMANAGEDLG_H__EBAAB06E_9410_4645_8A93_DB5274DB3B6B__INCLUDED_)
#define AFX_DATAMANAGEDLG_H__EBAAB06E_9410_4645_8A93_DB5274DB3B6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataManageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataManageDlg dialog

class CDataManageDlg : public CDialog
{
// Construction
public:
	CDataManageDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDataManageDlg)
	enum { IDD = IDD_DATA_MANAGE };
	CBCGPButton	m_btnRestore;
	CBCGPButton	m_btnBackup;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataManageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDataManageDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBackup();
	afx_msg void OnRestore();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAMANAGEDLG_H__EBAAB06E_9410_4645_8A93_DB5274DB3B6B__INCLUDED_)
