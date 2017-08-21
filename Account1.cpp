// Account1.cpp: implementation of the CAccount class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Account.h"
#include "Account1.h"
#include "MoneyOper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAccount::CAccount():CDataBase(_T("Account"),_T("AccountIndex"))
{
	 m_type = ACCOUNT_MONEY;
     m_dwAccountBase = 0.0;
	 m_dwAccountLeft = 0.0;
	 m_dwAccountMonth = 0.0;

	 m_childMoney.RemoveAll();
}

CAccount::~CAccount()
{
     for(int i=0;i<m_childMoney.GetSize();i++)
	 {
		 CMoneyOper* pMoney = m_childMoney.GetAt(i);
		 delete pMoney;
		 pMoney = NULL;
	 }
	 m_childMoney.RemoveAll();
}
BOOL CAccount::LoadInfo(CADORecordset& rs)
{
	BOOL bRet = TRUE;

	bRet &= rs.GetFieldValue(_T("AccountIndex"),m_nID);
	bRet &= rs.GetFieldValue(_T("AccountName"),m_strAccountName);
	bRet &= rs.GetFieldValue(_T("AccountBase"),m_dwAccountBase);
	bRet &= rs.GetFieldValue(_T("AccountType"),(int&)m_type);
	bRet &= rs.GetFieldValue(_T("AccountPower"),m_strAccountPower);
	    
	SetDesc(m_strAccountName);
	
	return bRet;
}
BOOL CAccount::SaveInfo(CADORecordset& rs)
{
	BOOL bRet = TRUE;

	bRet &= rs.SetFieldValue("AccountName",m_strAccountName);
	bRet &= rs.SetFieldValue("AccountBase",m_dwAccountBase);
	bRet &= rs.SetFieldValue("AccountType",(int)m_type);
	bRet &= rs.SetFieldValue("AccountPower",m_strAccountPower);

	return bRet;
}
BOOL CAccount::SaveToDB(CADODatabase* pDB,BOOL bChild /* = TRUE */)
{
	
	BOOL bRet = CDataBase::SaveToDB(pDB);

	//Save the child object
	if(bChild)
	{
		for(int i=0; i<m_childMoney.GetSize();i++)
		{
			bRet &= m_childMoney.GetAt(i)->SaveToDB(pDB);
		}
	}

	return bRet;
}
BOOL CAccount::DeleteFromDB(CADODatabase* pDB)
{
	BOOL bRet = TRUE;

	//Delete the child object
	for(int i=0; i<m_childMoney.GetSize();i++)
	{
		bRet &= m_childMoney.GetAt(i)->DeleteFromDB(pDB);
	}	
    bRet &= CDataBase::DeleteFromDB(pDB);

	return bRet;
}
void CAccount::ComputerMoney(COleDateTime timeCur)
{
	COleDateTime time1,time2,time;
	time1.SetDate(timeCur.GetYear(),timeCur.GetMonth(),1);
	if(timeCur.GetMonth() == 12)
        time.SetDate(timeCur.GetYear()+1,1,1);
	else
	    time.SetDate(timeCur.GetYear(),timeCur.GetMonth()+1,1);
	time2 = time-COleDateTimeSpan(1,0,0,0);

    CMoneyOper* pMoney;
    m_dwAccountLeft = m_dwAccountBase;
	m_dwAccountMonth = 0.0;

	for(int i=0 ;i<m_childMoney.GetSize();i++)
	{
		 pMoney = m_childMoney.GetAt(i);

		 if(pMoney->m_timeCreate <= timeCur)
             m_dwAccountLeft += pMoney->m_dwMoneySum;

         time = pMoney->m_timeCreate;
		 if(time >= time1 && time <=time2 )
			 m_dwAccountMonth +=pMoney->m_dwMoneySum;
	}
}
void CAccount::DeleteMoney(CMoneyOper* pMoney)
{
	ASSERT(pMoney!=NULL);
	//Delete Money from the Account
	 for(int i=0; i<m_childMoney.GetSize();i++)
	 {
		 CMoneyOper* pFound = m_childMoney.GetAt(i);
		 if(pFound->GetID() == pMoney->GetID())
		 {
			 m_childMoney.RemoveAt(i);
			 //Delete the memory
			 delete pMoney;
			 pMoney = NULL;
			 break;
		 }
	 }
}