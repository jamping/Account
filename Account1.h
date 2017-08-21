// Account1.h: interface for the CAccount class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCOUNT1_H__42AFAE7B_14B3_4AB1_967E_6C4A1DC5C30F__INCLUDED_)
#define AFX_ACCOUNT1_H__42AFAE7B_14B3_4AB1_967E_6C4A1DC5C30F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataBase.h"

class CMoneyOper;

class CAccount : public CDataBase  
{
public:
	enum AccountType{ ACCOUNT_TOTAL=0,ACCOUNT_BANK,ACCOUNT_MONEY };

	CAccount();
	virtual ~CAccount();  
	
	void ComputerMoney(COleDateTime timeCur); 
	void DeleteMoney(CMoneyOper* pMoney);
public:
	AccountType  m_type;
	CString      m_strAccountName;
	CString      m_strAccountPower;
	double       m_dwAccountBase;
	double       m_dwAccountLeft;
	double       m_dwAccountMonth;

	CArray<CMoneyOper*,CMoneyOper*>  m_childMoney;
public:
	virtual BOOL LoadInfo(CADORecordset& rs);
	virtual BOOL SaveInfo(CADORecordset& rs);
		
	virtual BOOL SaveToDB(CADODatabase* pDB,BOOL bChild = TRUE);
	virtual BOOL DeleteFromDB(CADODatabase* pDB);
private:
    	
};

#endif // !defined(AFX_ACCOUNT1_H__42AFAE7B_14B3_4AB1_967E_6C4A1DC5C30F__INCLUDED_)
