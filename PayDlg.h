#if !defined(AFX_PAYDLG_H__EDA710D6_4190_4484_9468_77193008E20C__INCLUDED_)
#define AFX_PAYDLG_H__EDA710D6_4190_4484_9468_77193008E20C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PayDlg.h : header file
//
#include "Pay.h"
/////////////////////////////////////////////////////////////////////////////
// CPayDlg dialog

class CPayDlg : public CDialog
{
// Construction
public:
	enum PayDlgType
	{
		NEW_GET=0,
		EDIT_GET,
		NEW_PAY,
		EDIT_PAY
	};

	CPayDlg(PayDlgType type,CWnd* pParent = NULL);   // standard constructor
 
	void GetValue(CPay * pPay);
	void SetValue(const CPay* pPay);
// Dialog Data
	//{{AFX_DATA(CPayDlg)
	enum { IDD = IDD_PAY };
	CBCGPButton	m_btnOk;
	CBCGPButton	m_btnCancel;
	CBCGPButton	m_btnIntoAccount;
	CBCGPMaskEdit	m_btnMoney;
	CBCGPAnimCtrl	m_pic;
	CComboBox	m_comboCustomer;
	CString	m_strCustomer;
	double	m_dwGetMoney;
	double	m_dwGettedMoney;
	double	m_dwLeftMoney;
	CString	m_strRemark;
	CString	m_strGetPay;
	CString	m_strGettedPay;
	COleDateTime	m_time;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPayDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	PayDlgType   m_type;

	// Generated message map functions
	//{{AFX_MSG(CPayDlg)
	afx_msg void OnSaveCustomer();
	afx_msg void OnGetpayIntoAccount();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAYDLG_H__EDA710D6_4190_4484_9468_77193008E20C__INCLUDED_)
