// MoneyOper.cpp: implementation of the CMoneyOper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Account.h"
#include "MoneyOper.h"
#include "Account1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMoneyOper::CMoneyOper():CDataBase(_T("MoneyTable"),_T("MoneyIndex"))
{
	m_dwMoneyIn = 0.0;
	m_dwMoneyOut = 0.0;
	m_dwMoneySum = 0.0;
	m_strMoneyPower = _T("³öÄÉ");

	m_pAccount = NULL;
}
CMoneyOper::~CMoneyOper()
{

}
BOOL CMoneyOper::LoadInfo(CADORecordset& rs)
{
	BOOL bRet = TRUE;

	bRet &= rs.GetFieldValue(_T("MoneyIndex"),m_nID);
	bRet &= rs.GetFieldValue(_T("MoneyAccount"),m_nAccountID);
	bRet &= rs.GetFieldValue(_T("MoneyRecordTime"),m_timeRecord);
    bRet &= rs.GetFieldValue(_T("MoneyCreateTime"),m_timeCreate);
	bRet &= rs.GetFieldValue(_T("MoneySerial"),m_strMoneySerial);
	bRet &= rs.GetFieldValue(_T("MoneyUser"),m_strMoneyUser);
	bRet &= rs.GetFieldValue(_T("MoneyType"),m_strMoneyType);
	bRet &= rs.GetFieldValue(_T("MoneyToken"),m_strMoneyToken);
	bRet &= rs.GetFieldValue(_T("MoneyReason"),m_strMoneyReason);
	bRet &= rs.GetFieldValue(_T("MoneyIn"),m_dwMoneyIn);
	bRet &= rs.GetFieldValue(_T("MoneyOut"),m_dwMoneyOut);
	bRet &= rs.GetFieldValue(_T("MoneySum"),m_dwMoneySum);
	bRet &= rs.GetFieldValue(_T("MoneyMan"),m_strMoneyMan);
	bRet &= rs.GetFieldValue(_T("MoneyRemark"),m_strMoneyRemark);
	bRet &= rs.GetFieldValue(_T("MoneyPower"),m_strMoneyPower);

 	SetDesc(m_pAccount->GetDesc());

	return bRet;
}
BOOL CMoneyOper::SaveInfo(CADORecordset& rs)
{
	BOOL bRet = TRUE;

	bRet &= rs.SetFieldValue(_T("MoneyAccount"),m_nAccountID);
	bRet &= rs.SetFieldValue(_T("MoneyRecordTime"),m_timeRecord.Format("%Y-%m-%d"));
    bRet &= rs.SetFieldValue(_T("MoneyCreateTime"),m_timeCreate.Format("%Y-%m-%d"));
	bRet &= rs.SetFieldValue(_T("MoneySerial"),m_strMoneySerial);
	bRet &= rs.SetFieldValue(_T("MoneyUser"),m_strMoneyUser);
	bRet &= rs.SetFieldValue(_T("MoneyType"),m_strMoneyType);
	bRet &= rs.SetFieldValue(_T("MoneyToken"),m_strMoneyToken);
	bRet &= rs.SetFieldValue(_T("MoneyReason"),m_strMoneyReason);
	bRet &= rs.SetFieldValue(_T("MoneyIn"),m_dwMoneyIn);
	bRet &= rs.SetFieldValue(_T("MoneyOut"),m_dwMoneyOut);
	bRet &= rs.SetFieldValue(_T("MoneySum"),m_dwMoneySum);
	bRet &= rs.SetFieldValue(_T("MoneyMan"),m_strMoneyMan);
	bRet &= rs.SetFieldValue(_T("MoneyRemark"),m_strMoneyRemark);
	bRet &= rs.SetFieldValue(_T("MoneyPower"),m_strMoneyPower);

	return bRet;
}
void CMoneyOper::AddTo(CAccount* pAccount)
{
	ASSERT(pAccount!=NULL);

	if( m_pAccount!=NULL )
	{
		if(m_pAccount->GetID() == pAccount->GetID())
			return;
        //Delete from the old Account
        for(int i=0;i<m_pAccount->m_childMoney.GetSize();i++)
		{
			if( GetID() == m_pAccount->m_childMoney.GetAt(i)->GetID())
			{
                 m_pAccount->m_childMoney.RemoveAt(i);
				 break;
			}
		}
	}
	
	m_pAccount = pAccount;
	m_pAccount->m_childMoney.Add(this);
	m_nAccountID = m_pAccount->GetID();	

}
