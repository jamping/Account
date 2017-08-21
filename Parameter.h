// Parameter.h: interface for the CParameter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARAMETER_H__780AF6DF_5002_4641_9996_CB6DA95F7BCE__INCLUDED_)
#define AFX_PARAMETER_H__780AF6DF_5002_4641_9996_CB6DA95F7BCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataBase.h"

class CParameter : public CDataBase  
{
public:
	enum ParameterType
	{
		NONE_TYPE=0,
		INCOME_TYPE,
		PAY_TYPE,
		PAY_ITEM_TYPE,
		CUSTOMER,
		OWNER
	};

	CParameter(ParameterType type = NONE_TYPE);
	virtual ~CParameter();
	
	void SetValue(CString strValue) { m_strValue=strValue;SetDesc(strValue); }
	CString GetValue() { return m_strValue; }
public:
	virtual BOOL LoadInfo(CADORecordset& rs);
	virtual BOOL SaveInfo(CADORecordset& rs);
private:
	ParameterType  m_type;
	CString        m_strValue;
};

#endif // !defined(AFX_PARAMETER_H__780AF6DF_5002_4641_9996_CB6DA95F7BCE__INCLUDED_)
