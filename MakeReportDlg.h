#if !defined(AFX_MAKEREPORTDLG_H__76CE9B6E_7043_48DF_81ED_AA9E737294BA__INCLUDED_)
#define AFX_MAKEREPORTDLG_H__76CE9B6E_7043_48DF_81ED_AA9E737294BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MakeReportDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMakeReportDlg dialog

class CMakeReportDlg : public CDialog
{
// Construction
public:
	CMakeReportDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMakeReportDlg)
	enum { IDD = IDD_MAKE_REPORT };
	CListBox	m_listAccount;
	CComboBox	m_comboPayType;
	CComboBox	m_comboPayItemType;
	CComboBox	m_comboOwner;
	CComboBox	m_comboIncomeType;
	CComboBox	m_comboCustomer;
	BOOL	m_bMoney;
	BOOL	m_bTime;
	CString	m_strCustomer;
	CString	m_strIncomeType;
	CString	m_strOwner;
	CString	m_strPayItemType;
	CString	m_strPayType;
	int		m_nType;
	double	m_dwMoney1;
	double	m_dwMoney2;
	CString	m_strNumber;
	CString	m_strRemark;
	COleDateTime	m_time1;
	COleDateTime	m_time2;
	//}}AFX_DATA
    CArray<CAccount*,CAccount*>   m_listSelAccount;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMakeReportDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:   
	void GetAccounts();
    void InitList(CComboBox& ctlList,int nType);
	// Generated message map functions
	//{{AFX_MSG(CMakeReportDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnCheckTime();
	afx_msg void OnCheckMoney();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAKEREPORTDLG_H__76CE9B6E_7043_48DF_81ED_AA9E737294BA__INCLUDED_)
