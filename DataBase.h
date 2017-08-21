// DataBase.h: interface for the CDataBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABASE_H__FE01C1ED_E43E_44A8_82B3_B132D8048B2B__INCLUDED_)
#define AFX_DATABASE_H__FE01C1ED_E43E_44A8_82B3_B132D8048B2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDataBase  
{
public:
	CDataBase(CString strTabaleName,CString strKeyName);
	virtual ~CDataBase();
    
	int  GetID() { return m_nID; }
	void SetID(int nID) { m_nID = nID; }
	int NewID(CADODatabase* pDB);

	CString GetDesc() { return m_strDesc; }
	void SetDesc(CString strDesc) { m_strDesc=strDesc; }
public:
	virtual BOOL LoadInfo(CADORecordset& rs)=0;
	virtual BOOL SaveInfo(CADORecordset& rs)=0;

	virtual BOOL SaveToDB(CADODatabase* pDB,BOOL bChild = TRUE);
	virtual BOOL DeleteFromDB(CADODatabase* pDB);
protected:
	CString m_strTableName;
    CString m_strKeyName;
	int     m_nID;
	CString m_strDesc;	
	

};

#endif // !defined(AFX_DATABASE_H__FE01C1ED_E43E_44A8_82B3_B132D8048B2B__INCLUDED_)
