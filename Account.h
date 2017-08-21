// Account.h : main header file for the ACCOUNT application
//

#if !defined(AFX_ACCOUNT_H__B95B7533_23F2_47B8_8A5F_6035963974EE__INCLUDED_)
#define AFX_ACCOUNT_H__B95B7533_23F2_47B8_8A5F_6035963974EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "User.h"
#include "Account1.h"
/////////////////////////////////////////////////////////////////////////////
// CAccountApp:
// See Account.cpp for the implementation of this class
//

class CAccountApp : public CWinApp,
					public CBCGPWorkspace
{
public:
	CAccountApp();
	
	CADODatabase* GetDB() { return m_db; }
    CDataBase* GetUser(int i=0);
	int GetAccountType() { return m_nAccountType; }
	void SetAccountType(int nType) { m_nAccountType = nType; }
	
	CArray<CAccount*,CAccount*>& GetAccountList( int nType=0 );
	void SetAccount(CAccount* pAccount);

    COleDateTime   m_timeCur;
private:
	CADODatabase*  m_db;
    CDataBase*     m_user[2];	
    int            m_nAccountType;
	CArray<CAccount*,CAccount*>  m_listTotalAccount;
	CArray<CAccount*,CAccount*>  m_listBankAccount;
	CArray<CAccount*,CAccount*>  m_listMoneyAccount;
    
	void Init();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccountApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL
// Implementation
	//{{AFX_MSG(CAccountApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CAccountApp theApp;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCOUNT_H__B95B7533_23F2_47B8_8A5F_6035963974EE__INCLUDED_)
