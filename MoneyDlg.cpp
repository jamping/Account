// MoneyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Account.h"
#include "MoneyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMoneyDlg dialog


CMoneyDlg::CMoneyDlg(UINT nType,CWnd* pParent /* = NULL */)
	: CDialog(CMoneyDlg::IDD, pParent),m_nType(nType)
{
	//{{AFX_DATA_INIT(CMoneyDlg)
	m_strAccountName = _T("");
	m_strCustomerName = _T("");
	m_strIncomeType = _T("");
	m_timeInput = COleDateTime::GetCurrentTime();
	m_dwMoney = 0.00;
	m_strNumber = _T("");
	m_strOwner = _T("");
	m_strPayItemType = _T("");
	m_strPayType = _T("");
	m_strRemark = _T("");
	//}}AFX_DATA_INIT
	m_pSelAccount = NULL;
}


void CMoneyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMoneyDlg)
	DDX_Control(pDX, IDC_TYPE, m_pic);
	DDX_Control(pDX, IDC_PAY_TYPE, m_comboPayType);
	DDX_Control(pDX, IDC_PAY_ITEM_TYPE, m_comboPayItemType);
	DDX_Control(pDX, IDC_OWNER, m_comboOwner);
	DDX_Control(pDX, IDC_INCOME_TYPE, m_comboIncomeType);
	DDX_Control(pDX, IDC_CUSTOMER_NAME, m_comboCustomer);
	DDX_Control(pDX, IDC_ACCOUNT_NAME, m_comboAccount);
	DDX_Control(pDX, IDC_MONEY, m_editMoney);
	DDX_CBString(pDX, IDC_ACCOUNT_NAME, m_strAccountName);
	DDX_CBString(pDX, IDC_CUSTOMER_NAME, m_strCustomerName);
	DDX_CBString(pDX, IDC_INCOME_TYPE, m_strIncomeType);
	DDX_DateTimeCtrl(pDX, IDC_INPUT_TIME, m_timeInput);
	DDX_Text(pDX, IDC_MONEY, m_dwMoney);
	DDX_Text(pDX, IDC_NUMBER, m_strNumber);
	DDX_CBString(pDX, IDC_OWNER, m_strOwner);
	DDX_CBString(pDX, IDC_PAY_ITEM_TYPE, m_strPayItemType);
	DDX_CBString(pDX, IDC_PAY_TYPE, m_strPayType);
	DDX_Text(pDX, IDC_REMARK, m_strRemark);
	//}}AFX_DATA_MAP
}
void CMoneyDlg::GetValue(CMoneyOper* pMoney)
{	
	pMoney->AddTo(m_pSelAccount);
    pMoney->m_strMoneySerial = m_strNumber;
	pMoney->m_strMoneyUser = m_strCustomerName;
	pMoney->m_timeCreate.SetDate(m_timeInput.GetYear(),m_timeInput.GetMonth(),m_timeInput.GetDay());
	pMoney->m_timeRecord.SetDate(m_timeInput.GetYear(),m_timeInput.GetMonth(),m_timeInput.GetDay());	
	pMoney->m_strMoneyReason = m_strIncomeType;
	pMoney->m_strMoneyToken = m_strPayItemType;
	pMoney->m_strMoneyMan = m_strOwner;
	pMoney->m_strMoneyRemark = m_strRemark;
	pMoney->m_strMoneyType = m_strPayType;

	switch(m_nType)
	{
	case NEW_GET:
	case EDIT_GET:
	    pMoney->m_dwMoneyIn = m_dwMoney;
		pMoney->m_dwMoneySum = m_dwMoney;
		break;
	case NEW_PAY:
	case EDIT_PAY:
        pMoney->m_dwMoneyOut = m_dwMoney;
		pMoney->m_dwMoneySum = -m_dwMoney;
		break;
	}
}
void CMoneyDlg::SetValue(const CMoneyOper* pMoney)
{    
    m_strNumber = pMoney->m_strMoneySerial;
	m_pSelAccount = pMoney->m_pAccount;
	m_strCustomerName = pMoney->m_strMoneyUser;
	m_timeInput = pMoney->m_timeCreate;
	m_strIncomeType = pMoney->m_strMoneyReason;
	m_strPayItemType = pMoney->m_strMoneyToken;
	m_strOwner = pMoney->m_strMoneyMan;
	m_strRemark = pMoney->m_strMoneyRemark;
	m_strPayType = pMoney->m_strMoneyType;

	switch(m_nType)
	{
	case 0:
	case 1:
	    m_dwMoney = pMoney->m_dwMoneyIn;
		break;
	case 2:
	case 3:
        m_dwMoney = pMoney->m_dwMoneyOut;
		break;
	}
}

BEGIN_MESSAGE_MAP(CMoneyDlg, CDialog)
	//{{AFX_MSG_MAP(CMoneyDlg)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMoneyDlg message handlers

void CMoneyDlg::OnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if(m_strCustomerName.IsEmpty())
	{
		MessageBox("客户名称不能为空！","错误",MB_OK|MB_ICONWARNING);
		return ;
	}
	CString strSql,str;
	BOOL bRet = TRUE;
	strSql.Format("select * from Parameter where ParameterValue='%s' and ParameterType=%d",m_strCustomerName,4);

	CADORecordset rs(theApp.GetDB());
	bRet = rs.Open(strSql,CADORecordset::openQuery);
	if(bRet)
	{
		if(rs.GetRecordCount()==0)
		{
			bRet &= rs.AddNew();
			bRet &= rs.SetFieldValue("ParameterType",4);
			bRet &= rs.SetFieldValue("ParameterValue",m_strCustomerName);
			bRet &= rs.Update();

			m_comboCustomer.AddString(m_strCustomerName);
		}
		rs.Close();
	}

	MessageBox(bRet ? _T("客户添加成功！"):_T("客户添加失败！"));
}

BOOL CMoneyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UINT nID = 0;
	switch(m_nType)
	{
	case NEW_GET:
		nID = IDB_NEW_GET;
		break;
	case EDIT_GET:
		nID = IDB_EDIT_GET;
		break;
	case NEW_PAY:
		nID = IDB_NEW_PAY;
		break;
	case EDIT_PAY:
		nID = IDB_EDIT_PAY;
		break;
	}
    CBitmap bmp;
	bmp.LoadBitmap(nID);
 	BITMAP bmpobj;
 	bmp.GetBitmap(&bmpobj);

	m_pic.SetBitmap(nID,bmpobj.bmWidth);
    DeleteObject(HBITMAP(&bmpobj));

	m_editMoney.EnableCalculatorButton ();
    m_editMoney.DisableMask();					// Don't use the mask
	m_editMoney.SetValidChars(_T("1234567890."));	// Valid string characters 

	int nSel = 0;
	for(int i=0;i<theApp.GetAccountList(theApp.GetAccountType()).GetSize();i++)
	{
		CAccount* pAccount = theApp.GetAccountList(theApp.GetAccountType()).GetAt(i);
		int nIndex = m_comboAccount.AddString(pAccount->GetDesc());
		m_comboAccount.SetItemData(nIndex,(DWORD)pAccount);

		if( m_pSelAccount && m_pSelAccount->GetID()==pAccount->GetID())
			nSel = nIndex;
	}
	m_comboAccount.SetCurSel(nSel);
	
	InitList(m_comboCustomer,4,m_strCustomerName);
	InitList(m_comboOwner,5,m_strOwner);
	InitList(m_comboIncomeType,1,m_strIncomeType);
	InitList(m_comboPayType,2,m_strPayType);
	InitList(m_comboPayItemType,3,m_strPayItemType);    

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CMoneyDlg::InitList(CComboBox& ctlList,int nType,CString strInit)
{
	CString strSql,str;
	strSql.Format("select ParameterValue from Parameter where ParameterType=%d",nType);

	CADORecordset rs(theApp.GetDB());
	if(rs.Open(strSql,CADORecordset::openQuery))
	{
         while (!rs.IsEOF())
         {
			 rs.GetFieldValue(_T("ParameterValue"),str);
			 ctlList.AddString(str);

			 rs.MoveNext();
         }
		 rs.Close();
	}
	int nIndex = ctlList.SelectString(0,strInit);
	if(nIndex == -1)
		ctlList.SetWindowText(strInit);
}

void CMoneyDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();

	int nIndex = m_comboAccount.GetCurSel();
	if(nIndex!=-1)
	{
         m_pSelAccount = (CAccount*)m_comboAccount.GetItemData(nIndex);
	}
    if(m_dwMoney == 0.)
	{
		MessageBox(_T("金额不能为0"),_T("错误"),MB_OK|MB_ICONWARNING);
		return;
	}
	CDialog::OnOK();
}

