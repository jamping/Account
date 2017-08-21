#if !defined(AFX_MONEYMOVEDLG_H__5BDF80D5_EAE4_4BC5_8557_473608E9757E__INCLUDED_)
#define AFX_MONEYMOVEDLG_H__5BDF80D5_EAE4_4BC5_8557_473608E9757E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MoneyMoveDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMoneyMoveDlg dialog

class CMoneyMoveDlg : public CDialog
{
// Construction
public:
	CMoneyMoveDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMoneyMoveDlg)
	enum { IDD = IDD_MONEY_MOVE };
	CBCGPMaskEdit	m_editMoney;
	CComboBox	m_comboAccount2;
	CComboBox	m_comboAccount1;
	double	m_dwMoney;
	CString	m_strRemark;
	COleDateTime	m_time;
	//}}AFX_DATA

    CAccount * m_pAccountSrc;
	CAccount * m_pAccountDst;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMoneyMoveDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMoneyMoveDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONEYMOVEDLG_H__5BDF80D5_EAE4_4BC5_8557_473608E9757E__INCLUDED_)
