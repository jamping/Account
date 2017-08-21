#if !defined(AFX_ACCOUNTLOGDLG_H__98AF13DD_2BA8_410C_8F94_B759B3A0D003__INCLUDED_)
#define AFX_ACCOUNTLOGDLG_H__98AF13DD_2BA8_410C_8F94_B759B3A0D003__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AccountLogDlg.h : header file
//
#include "mylist.h"
/////////////////////////////////////////////////////////////////////////////
// CAccountLogDlg dialog

class CAccountLogDlg : public CDialog
{
// Construction
public:
	CAccountLogDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAccountLogDlg)
	enum { IDD = IDD_ACCOUNT_LOG };
	CBCGPButton	m_btnEdit;
	CBCGPButton	m_btnDel;
	CMyList	m_list;
	CString	m_strLastDayLeft;
	CString	m_strTodayIncome;
	CString	m_strTodayLeft;
	CString	m_strTodayOutcome;
	//}}AFX_DATA

    void ShowMoneyOper(COleDateTime timeCur,int nAccountType =0);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccountLogDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    void EditListItem(CMyList& listCtrl,int nItem);
	// Generated message map functions
	//{{AFX_MSG(CAccountLogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDel();
	afx_msg void OnEdit();
	//}}AFX_MSG
	afx_msg void OnUpdateEdit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDel(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCOUNTLOGDLG_H__98AF13DD_2BA8_410C_8F94_B759B3A0D003__INCLUDED_)
