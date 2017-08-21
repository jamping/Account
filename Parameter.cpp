// Parameter.cpp: implementation of the CParameter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Account.h"
#include "Parameter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParameter::CParameter(ParameterType type /* = NONE_TYPE */)
:CDataBase(_T("Parameter"),_T("ParameterIndex")),m_type(type)
{

}

CParameter::~CParameter()
{

}
BOOL CParameter::LoadInfo(CADORecordset& rs)
{
	BOOL bRet = TRUE;

	bRet &= rs.GetFieldValue(_T("ParameterIndex"),m_nID);
	bRet &= rs.GetFieldValue(_T("ParameterType"),(int&)m_type);
	bRet &= rs.GetFieldValue(_T("ParameterValue"),m_strValue);
    
	SetDesc(m_strValue);

	return bRet;
}
BOOL CParameter::SaveInfo(CADORecordset& rs)
{
	BOOL bRet = TRUE;
	CDes des;

	bRet &= rs.SetFieldValue("ParameterType",(int)m_type);
	bRet &= rs.SetFieldValue("ParameterValue",m_strValue);

	return bRet;
}
