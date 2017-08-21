// Pay.h: interface for the CPay class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAY_H__7016797F_18AA_4486_89BE_028730638702__INCLUDED_)
#define AFX_PAY_H__7016797F_18AA_4486_89BE_028730638702__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataBase.h"

class CPay : public CDataBase  
{
public:
	CPay();
	virtual ~CPay();
public:
	virtual BOOL LoadInfo(CADORecordset& rs);
	virtual BOOL SaveInfo(CADORecordset& rs);
public:
	COleDateTime m_timePay;
	CString      m_strUserName;
	double       m_dwPaySum;
	double       m_dwPayedSum;
	double       m_dwPayLeft;
	CString      m_strPayRemark;
	CString      m_strCustomer;
};

#endif // !defined(AFX_PAY_H__7016797F_18AA_4486_89BE_028730638702__INCLUDED_)
