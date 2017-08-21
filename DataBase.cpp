// DataBase.cpp: implementation of the CDataBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Account.h"
#include "DataBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataBase::CDataBase(CString strTabaleName,CString strKeyName)
:m_strTableName(strTabaleName),m_strKeyName(strKeyName)
{
    m_nID = 0;
	m_strDesc = _T("");
}

CDataBase::~CDataBase()
{

}

BOOL CDataBase::SaveToDB(CADODatabase* pDB,BOOL bChild /* = TRUE */)
{
	ASSERT(GetID() > 0);

	BOOL bRet = TRUE;
	CString strSql;

	strSql.Format("select * from %s where %s=%d",m_strTableName,m_strKeyName,GetID());

	CADORecordset rs(pDB);
	bRet=rs.Open(strSql,CADORecordset::openQuery);
	if(bRet)
	{
		if(rs.GetRecordCount()==0)
		{
			bRet &= rs.AddNew();
			bRet &= rs.SetFieldValue(m_strKeyName,GetID());
		}
		else
		{
			rs.Edit();
		}

		bRet &= SaveInfo(rs);

		bRet &= rs.Update();
		rs.Close();
	}

	return bRet;
}
BOOL CDataBase::DeleteFromDB(CADODatabase* pDB)
{
	BOOL bRet = TRUE;

	CString strSql;
	strSql.Format("delete from %s where %s=%d",m_strTableName,m_strKeyName,GetID());
	
	bRet = pDB->Execute(strSql);	

	return bRet;
}

int CDataBase::NewID(CADODatabase* pDB)
{
	int nID = -1;
	CString strSql;
	strSql.Format("select max(%s) as newid from %s",m_strKeyName,m_strTableName);

    CADORecordset rs(pDB);
	BOOL bRet=rs.Open(strSql,CADORecordset::openQuery);
	if(bRet)
	{
         bRet &= rs.GetFieldValue(_T("newid"),nID);

		 rs.Close();
    }

	return nID+1;
	
}
