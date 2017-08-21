#if !defined(AFX_SEARCHDLG_H__F9488BC0_116D_4223_A3AD_B6BE157A06D5__INCLUDED_)
#define AFX_SEARCHDLG_H__F9488BC0_116D_4223_A3AD_B6BE157A06D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg dialog

class CSearchDlg : public CDialog
{
// Construction
public:
	CSearchDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSearchDlg)
	enum { IDD = IDD_SEARCH };
	CComboBox	m_comboCustomer;
	CString	m_strCustomer;
	CString	m_strRemark;
	COleDateTime	m_time1;
	COleDateTime	m_time2;
	BOOL	m_bTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSearchDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnCheckTime();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHDLG_H__F9488BC0_116D_4223_A3AD_B6BE157A06D5__INCLUDED_)
