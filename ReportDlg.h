#if !defined(AFX_REPORTDLG_H__2EDB65A7_BE84_4950_B046_7555FEBDEFA8__INCLUDED_)
#define AFX_REPORTDLG_H__2EDB65A7_BE84_4950_B046_7555FEBDEFA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportDlg.h : header file
//
#include "MyList.h"
/////////////////////////////////////////////////////////////////////////////
// CReportDlg dialog

class CReportDlg : public CDialog
{
// Construction
public:
	CReportDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReportDlg)
	enum { IDD = IDD_REPORT };
	CBCGPButton	m_btnEdit;
	CBCGPButton	m_btnDel;
	CBCGPButton	m_btnMakeReport;
	CBCGPButton	m_btnMakeExcel;
	CMyList	m_list;
	//}}AFX_DATA

    void ShowMoneyOper();
    CArray<CMoneyOper*,CMoneyOper*>& GetMoneyList() { return m_listMoney; }
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void EditListItem(CMyList& listCtrl,int nItem);
    HRESULT AutoWrap(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, int cArgs...);

	CArray<CMoneyOper*,CMoneyOper*>   m_listMoney;
	// Generated message map functions
	//{{AFX_MSG(CReportDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnMakeExcel();
	afx_msg void OnMakeReport();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDel();
	afx_msg void OnEdit();
	//}}AFX_MSG
	afx_msg void OnUpdateMakeExcel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEdit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDel(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTDLG_H__2EDB65A7_BE84_4950_B046_7555FEBDEFA8__INCLUDED_)
