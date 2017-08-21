// MoneyOper.h: interface for the CMoneyOper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONEYOPER_H__AEBF047A_143B_404F_AEA0_03D9A75B58FF__INCLUDED_)
#define AFX_MONEYOPER_H__AEBF047A_143B_404F_AEA0_03D9A75B58FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataBase.h"

class CAccount;

class CMoneyOper : public CDataBase  
{
public:
	CMoneyOper();
	virtual ~CMoneyOper();
	
public:
	virtual BOOL LoadInfo(CADORecordset& rs);
	virtual BOOL SaveInfo(CADORecordset& rs);
   
	void AddTo(CAccount* pAccount);

	int              m_nAccountID;
	COleDateTime     m_timeRecord;
	COleDateTime     m_timeCreate;
	CString          m_strMoneySerial;
	CString          m_strMoneyUser;
	CString          m_strMoneyType;
	CString			 m_strMoneyToken;
	CString          m_strMoneyReason;
	double           m_dwMoneyIn;
	double           m_dwMoneyOut;
	double           m_dwMoneySum;
	CString          m_strMoneyMan;
	CString          m_strMoneyRemark;
	CString          m_strMoneyPower;

	CAccount*        m_pAccount;
};

#endif // !defined(AFX_MONEYOPER_H__AEBF047A_143B_404F_AEA0_03D9A75B58FF__INCLUDED_)
