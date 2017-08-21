// MakeReportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Account.h"
#include "MakeReportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMakeReportDlg dialog


CMakeReportDlg::CMakeReportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMakeReportDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMakeReportDlg)
	m_bMoney = FALSE;
	m_bTime = FALSE;
	m_strCustomer = _T("所有");
	m_strIncomeType = _T("");
	m_strOwner = _T("");
	m_strPayItemType = _T("");
	m_strPayType = _T("");
	m_nType = 0;
	m_dwMoney1 = 0.0;
	m_dwMoney2 = 0.0;
	m_strNumber = _T("");
	m_strRemark = _T("");
	m_time1 = COleDateTime::GetCurrentTime();
	m_time2 = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void CMakeReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMakeReportDlg)
	DDX_Control(pDX, IDC_LIST_ACCOUNT, m_listAccount);
	DDX_Control(pDX, IDC_COMBO_PAY_TYPE, m_comboPayType);
	DDX_Control(pDX, IDC_COMBO_PAY_ITEM_TYPE, m_comboPayItemType);
	DDX_Control(pDX, IDC_COMBO_OWNER, m_comboOwner);
	DDX_Control(pDX, IDC_COMBO_INCOME_TYPE, m_comboIncomeType);
	DDX_Control(pDX, IDC_COMBO_CUSTOMER, m_comboCustomer);
	DDX_Check(pDX, IDC_CHECK_MONEY, m_bMoney);
	DDX_Check(pDX, IDC_CHECK_TIME, m_bTime);
	DDX_CBString(pDX, IDC_COMBO_CUSTOMER, m_strCustomer);
	DDX_CBString(pDX, IDC_COMBO_INCOME_TYPE, m_strIncomeType);
	DDX_CBString(pDX, IDC_COMBO_OWNER, m_strOwner);
	DDX_CBString(pDX, IDC_COMBO_PAY_ITEM_TYPE, m_strPayItemType);
	DDX_CBString(pDX, IDC_COMBO_PAY_TYPE, m_strPayType);
	DDX_CBIndex(pDX, IDC_COMBO_TYPE, m_nType);
	DDX_Text(pDX, IDC_MONEY1, m_dwMoney1);
	DDX_Text(pDX, IDC_MONEY2, m_dwMoney2);
	DDX_Text(pDX, IDC_NUMBER, m_strNumber);
	DDX_Text(pDX, IDC_REMARK, m_strRemark);
	DDX_DateTimeCtrl(pDX, IDC_TIME1, m_time1);
	DDX_DateTimeCtrl(pDX, IDC_TIME2, m_time2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMakeReportDlg, CDialog)
	//{{AFX_MSG_MAP(CMakeReportDlg)
	ON_BN_CLICKED(IDC_CHECK_TIME, OnCheckTime)
	ON_BN_CLICKED(IDC_CHECK_MONEY, OnCheckMoney)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMakeReportDlg message handlers

BOOL CMakeReportDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_listAccount.AddString(_T("所有"));
	
	GetDlgItem(IDC_TIME1)->EnableWindow(m_bTime);
    GetDlgItem(IDC_TIME2)->EnableWindow(m_bTime);
	GetDlgItem(IDC_MONEY1)->EnableWindow(m_bMoney);
    GetDlgItem(IDC_MONEY2)->EnableWindow(m_bMoney);

	for(int i=0;i<theApp.GetAccountList(theApp.GetAccountType()).GetSize();i++)
	{
		CAccount* pAccount = theApp.GetAccountList(theApp.GetAccountType()).GetAt(i);

		int nIndex = m_listAccount.AddString(pAccount->GetDesc());
		m_listAccount.SetItemData(nIndex,(DWORD)pAccount);
	}
	InitList(m_comboCustomer,4);
	InitList(m_comboOwner,5);
	InitList(m_comboIncomeType,1);
	InitList(m_comboPayType,2);
	InitList(m_comboPayItemType,3);   

	COleDateTime timeMoreMonth,curTime = COleDateTime::GetCurrentTime();
	m_time1.SetDate(curTime.GetYear(),curTime.GetMonth(),1);
	if(curTime.GetMonth() == 12)
        timeMoreMonth.SetDate(curTime.GetYear()+1,1,1);
	else
	    timeMoreMonth.SetDate(curTime.GetYear(),curTime.GetMonth()+1,1);

	m_time2 = timeMoreMonth-COleDateTimeSpan(1,0,0,0);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMakeReportDlg::OnOK() 
{
	// TODO: Add extra validation here
	GetAccounts();
	if(m_listSelAccount.GetSize()==0)
	{
		MessageBox(_T("请选择账户！"));
		return;
	}
	if(m_bTime && m_time1>m_time2)
	{
		MessageBox(_T("起始时间大于结束时间！"));
		return;
	}
	if(m_bMoney && m_dwMoney1>m_dwMoney2)
	{
		MessageBox(_T("起始金额大于结束金额！"));
		return;
	}
	CDialog::OnOK();
}
void CMakeReportDlg::InitList(CComboBox& ctlList,int nType)
{
	ctlList.AddString(_T("所有"));

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
	ctlList.SetCurSel(0);
}

void CMakeReportDlg::OnCheckTime() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	GetDlgItem(IDC_TIME1)->EnableWindow(m_bTime);
    GetDlgItem(IDC_TIME2)->EnableWindow(m_bTime);

	m_bTime =!m_bTime;
}

void CMakeReportDlg::OnCheckMoney() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	GetDlgItem(IDC_MONEY1)->EnableWindow(m_bMoney);
    GetDlgItem(IDC_MONEY2)->EnableWindow(m_bMoney);

	m_bMoney =!m_bMoney;
}
void CMakeReportDlg::GetAccounts()
{
	m_listSelAccount.RemoveAll();

	int i =0;
	if(m_listAccount.GetSel(0)>0)
	{
		for(i=1;i<m_listAccount.GetCount();i++)
			m_listSelAccount.Add((CAccount*)m_listAccount.GetItemData(i));
	}
	else
	{
		int nCount = m_listAccount.GetSelCount();
		CArray<int,int> aryListBoxSel;
		
		aryListBoxSel.SetSize(nCount);
		m_listAccount.GetSelItems(nCount, aryListBoxSel.GetData()); 

		for(i=0;i<aryListBoxSel.GetSize();i++)
			m_listSelAccount.Add((CAccount*)m_listAccount.GetItemData(aryListBoxSel.GetAt(i)));

	}
}
