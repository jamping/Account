#if !defined(AFX_SETTINGDLG_H__643E8015_1E6F_43C6_A2F2_52A3F412380A__INCLUDED_)
#define AFX_SETTINGDLG_H__643E8015_1E6F_43C6_A2F2_52A3F412380A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingDlg.h : header file
//
#include "Parameter.h"

class CCustomEditListBox : public CBCGPEditListBox
{
public:
	CCustomEditListBox(CParameter::ParameterType type)
	{
		m_type = type;
	}
	CParameter::ParameterType GetType( ) { return m_type; }
    
	BOOL OnBeforeRemoveItem (int iItem)	
	{	
        CParameter* pParam = (CParameter*)GetItemData(iItem);
        BOOL bRet = pParam->DeleteFromDB(theApp.GetDB());

		delete pParam;
		pParam = NULL;

		return bRet;	
	}
	void OnAfterAddItem (int iItem)
	{
		 CParameter* pParam = new CParameter(GetType());
		 pParam->SetValue(GetItemText(iItem));
         pParam->SetID(pParam->NewID(theApp.GetDB()));
		 pParam->SaveToDB(theApp.GetDB());

		 SetItemData(iItem,(DWORD)pParam);
	}
	void OnAfterRenameItem (int iItem) 
	{
		CString str = GetItemText(iItem);
		
        CParameter* pParam = (CParameter*)GetItemData(iItem);
		pParam->SetValue(str);

		pParam->SaveToDB(theApp.GetDB());
	}
	void OnAfterMoveItemUp (int iItem)
	{
        CParameter* pParam1 = (CParameter*) GetItemData(iItem);
		CParameter* pParam2 = (CParameter*) GetItemData(iItem+1);

		int nID = pParam1->GetID();
        pParam1->SetID(pParam2->GetID());
        pParam2->SetID(nID);

		pParam1->SaveToDB(theApp.GetDB());
		pParam2->SaveToDB(theApp.GetDB());
	}
	void OnAfterMoveItemDown (int iItem) 
	{
        CParameter* pParam1 = (CParameter*) GetItemData(iItem);
		CParameter* pParam2 = (CParameter*) GetItemData(iItem-1);

		int nID = pParam1->GetID();
        pParam1->SetID(pParam2->GetID());
        pParam2->SetID(nID);
		
		pParam1->SaveToDB(theApp.GetDB());
		pParam2->SaveToDB(theApp.GetDB());
	}
private:
	CParameter::ParameterType  m_type;
	
};
/////////////////////////////////////////////////////////////////////////////
// CSettingDlg dialog

class CSettingDlg : public CDialog
{
// Construction
public:
	CSettingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingDlg)
	enum { IDD = IDD_SETTING };
	CCustomEditListBox	m_listPayType;
	CCustomEditListBox	m_listPayItemType;
	CCustomEditListBox	m_listOwner;
	CCustomEditListBox	m_listIncomeType;
	CCustomEditListBox	m_listCustomer;
	CComboBox	m_comboUsers;
	CString	m_strUserPass;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    void InitList(CCustomEditListBox& list);
	void ClearMem(CCustomEditListBox& list);
	// Generated message map functions
	//{{AFX_MSG(CSettingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnModify();
	afx_msg void OnSelchangeComboUsers();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGDLG_H__643E8015_1E6F_43C6_A2F2_52A3F412380A__INCLUDED_)
