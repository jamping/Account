#if !defined(AFX_MONEYDLG_H__E94A5861_433C_42E4_BF88_96E03AAEBAA0__INCLUDED_)
#define AFX_MONEYDLG_H__E94A5861_433C_42E4_BF88_96E03AAEBAA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MoneyDlg.h : header file
//
#include "MoneyOper.h"
/////////////////////////////////////////////////////////////////////////////
// CMoneyDlg dialog

class CMoneyDlg : public CDialog
{
// Construction
public:
	enum MoneyDlgType
	{
		NEW_GET=0,
		EDIT_GET,
		NEW_PAY,
		EDIT_PAY
	};

	CMoneyDlg(UINT nType,CWnd* pParent = NULL);   // standard constructor

    void GetValue(CMoneyOper* pMoney);
	void SetValue(const CMoneyOper* pMoney);

    CAccount * m_pSelAccount;

// Dialog Data
	//{{AFX_DATA(CMoneyDlg)
	enum { IDD = IDD_MONEY };
	CBCGPAnimCtrl	m_pic;
	CComboBox	m_comboPayType;
	CComboBox	m_comboPayItemType;
	CComboBox	m_comboOwner;
	CComboBox	m_comboIncomeType;
	CComboBox	m_comboCustomer;
	CComboBox	m_comboAccount;
	CBCGPMaskEdit	m_editMoney;
	CString	m_strAccountName;
	CString	m_strCustomerName;
	CString	m_strIncomeType;
	COleDateTime 	m_timeInput;
	double	m_dwMoney;
	CString	m_strNumber;
	CString	m_strOwner;
	CString	m_strPayItemType;
	CString	m_strPayType;
	CString	m_strRemark;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMoneyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    UINT     m_nType;

	void InitList(CComboBox& ctlList,int nType,CString strInit);
	// Generated message map functions
	//{{AFX_MSG(CMoneyDlg)
	afx_msg void OnSave();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONEYDLG_H__E94A5861_433C_42E4_BF88_96E03AAEBAA0__INCLUDED_)
