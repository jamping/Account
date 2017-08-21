#if !defined(AFX_INOUTDLG_H__C2F5B1A1_9FD3_4E17_81B9_EAF5186B9642__INCLUDED_)
#define AFX_INOUTDLG_H__C2F5B1A1_9FD3_4E17_81B9_EAF5186B9642__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InOutDlg.h : header file
//
#include "mylist.h"
/////////////////////////////////////////////////////////////////////////////
// CInOutDlg dialog

class CInOutDlg : public CDialog
{
// Construction
public:
	CInOutDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInOutDlg)
	enum { IDD = IDD_INANDOUT };
	CBCGPButton	m_btnSearchOut;
	CBCGPButton	m_btnSearchIn;
	CBCGPButton	m_btnModifyOut;
	CBCGPButton	m_btnModifyIn;
	CMyList	m_listOut;
	CMyList	m_listIn;
	CBCGPButton	m_btnDelOut;
	CBCGPButton	m_btnDelIn;
	CBCGPButton	m_btnAddOut;
	CBCGPButton	m_btnAddIn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInOutDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    void EditListItem(CMyList& listCtrl,int nItem,CString strSql);
	void ShowList(CMyList& listCtrl,CString strSql);
	void DeleteListAllItems(CMyList& listCtrl);
	// Generated message map functions
	//{{AFX_MSG(CInOutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnDblclkListIn(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListOut(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSearchin();
	afx_msg void OnAddin();
	afx_msg void OnModifyin();
	afx_msg void OnDelin();
	afx_msg void OnSearchout();
	afx_msg void OnAddout();
	afx_msg void OnModifyout();
	afx_msg void OnDelout();
	//}}AFX_MSG
	afx_msg void OnUpdateModifyIn(CCmdUI* pCmdUI);
	afx_msg void OnUpdateModifyOut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDelIn(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDelOut(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INOUTDLG_H__C2F5B1A1_9FD3_4E17_81B9_EAF5186B9642__INCLUDED_)
