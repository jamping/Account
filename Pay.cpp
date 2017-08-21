// Pay.cpp: implementation of the CPay class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Account.h"
#include "Pay.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPay::CPay():CDataBase(_T("GetPay"),_T("GetPayIndex"))
{
     m_dwPaySum = 0.0;
	 m_dwPayedSum = 0.0;
	 m_dwPayLeft = 0.0;
}

CPay::~CPay()
{

}
BOOL CPay::LoadInfo(CADORecordset& rs)
{
	BOOL bRet = TRUE;

	bRet &= rs.GetFieldValue(_T("GetPayIndex"),m_nID);
	bRet &= rs.GetFieldValue(_T("GetPayTime"),m_timePay);
	bRet &= rs.GetFieldValue(_T("GetPayUser"),m_strCustomer);
    bRet &= rs.GetFieldValue(_T("GetPaySum"),m_dwPaySum);
	bRet &= rs.GetFieldValue(_T("GetPaySum2"),m_dwPayedSum);
	bRet &= rs.GetFieldValue(_T("GetPaySum3"),m_dwPayLeft);
	bRet &= rs.GetFieldValue(_T("GetPayRemark"),m_strPayRemark);
	bRet &= rs.GetFieldValue(_T("GetPayPower"),m_strUserName);
	
 	SetDesc(m_strCustomer);

	return bRet;
}
BOOL CPay::SaveInfo(CADORecordset& rs)
{
	BOOL bRet = TRUE;

	bRet &= rs.SetFieldValue(_T("GetPayTime"),m_timePay.Format("%Y-%m-%d"));
    bRet &= rs.SetFieldValue(_T("GetPayUser"),m_strCustomer);
	bRet &= rs.SetFieldValue(_T("GetPaySum"),m_dwPaySum);
	bRet &= rs.SetFieldValue(_T("GetPaySum2"),m_dwPayedSum);
	bRet &= rs.SetFieldValue(_T("GetPaySum3"),m_dwPayLeft);
	bRet &= rs.SetFieldValue(_T("GetPayRemark"),m_strPayRemark);
	bRet &= rs.SetFieldValue(_T("GetPayPower"),m_strUserName);

	return bRet;
}