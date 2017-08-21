// User.h: interface for the CUser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USER_H__FE227360_FD17_404E_A648_9956DD3A9A5C__INCLUDED_)
#define AFX_USER_H__FE227360_FD17_404E_A648_9956DD3A9A5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataBase.h"

class CUser : public CDataBase  
{
public:
	CUser();
	virtual ~CUser();
    
	CString GetUserName() { return m_strUserName; }
	CString GetPassWord() { return m_strPassWord; }
	void SetPassWord(CString strPass) { m_strPassWord = strPass; }
public:
	virtual BOOL LoadInfo(CADORecordset& rs);
	virtual BOOL SaveInfo(CADORecordset& rs);
private:
	CString  m_strUserName;
	CString  m_strPassWord;
};

#endif // !defined(AFX_USER_H__FE227360_FD17_404E_A648_9956DD3A9A5C__INCLUDED_)
