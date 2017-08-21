// SettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Account.h"
#include "SettingDlg.h"
#include "Parameter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg dialog


CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg::IDD, pParent)
	,m_listCustomer(CParameter::CUSTOMER)
	,m_listOwner(CParameter::OWNER)
	,m_listIncomeType(CParameter::INCOME_TYPE)
	,m_listPayType(CParameter::PAY_TYPE)
	,m_listPayItemType(CParameter::PAY_ITEM_TYPE)
{
	//{{AFX_DATA_INIT(CSettingDlg)
	m_strUserPass = _T("");
	//}}AFX_DATA_INIT
}


void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingDlg)
	DDX_Control(pDX, IDC_PAY_TYPE, m_listPayType);
	DDX_Control(pDX, IDC_PAY_ITEM_TYPE, m_listPayItemType);
	DDX_Control(pDX, IDC_OWNER_LIST, m_listOwner);
	DDX_Control(pDX, IDC_INCOME_TYPE, m_listIncomeType);
	DDX_Control(pDX, IDC_CUSTOMER_LIST, m_listCustomer);
	DDX_Control(pDX, IDC_COMBO_USERS, m_comboUsers);
	DDX_Text(pDX, IDC_USER_PASSWORD, m_strUserPass);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CSettingDlg)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	ON_CBN_SELCHANGE(IDC_COMBO_USERS, OnSelchangeComboUsers)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg message handlers

BOOL CSettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_listPayType.SetStandardButtons ();
	m_listCustomer.SetStandardButtons ();
	m_listIncomeType.SetStandardButtons ();
	m_listOwner.SetStandardButtons ();
	m_listPayItemType.SetStandardButtons ();

	InitList(m_listCustomer);
	InitList(m_listOwner);
	InitList(m_listIncomeType);
	InitList(m_listPayType);
	InitList(m_listPayItemType);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSettingDlg::OnModify() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	int nIndex = m_comboUsers.GetCurSel();
    if(nIndex != -1)
	{
		CUser* pUser = (CUser*)theApp.GetUser(nIndex);
		pUser->SetPassWord(m_strUserPass);
		pUser->SaveToDB(theApp.GetDB());

		MessageBox(_T("密码修改成功！"),_T("流水账"));
	}
}

void CSettingDlg::OnSelchangeComboUsers() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_comboUsers.GetCurSel();
    if(nIndex != -1)
	{
		CUser* pUser = (CUser*)theApp.GetUser(nIndex);
		m_strUserPass = pUser->GetPassWord();
	}
	UpdateData(FALSE);
}
void CSettingDlg::InitList(CCustomEditListBox& list)
{
	CString strSql;
	strSql.Format("select * from Parameter where ParameterType=%d",(int)list.GetType());

	CADORecordset rs(theApp.GetDB());
	if(rs.Open(strSql,CADORecordset::openQuery))
	{
         while (!rs.IsEOF())
         {
			 CParameter* pParam = new CParameter;
			 pParam->LoadInfo(rs);
			 list.AddItem(pParam->GetDesc(),(DWORD)pParam);

			 rs.MoveNext();
         }
		 rs.Close();
	}
}

void CSettingDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	ClearMem(m_listCustomer);
	ClearMem(m_listOwner);
	ClearMem(m_listIncomeType);
	ClearMem(m_listPayType);
	ClearMem(m_listPayItemType);
}
void CSettingDlg::ClearMem(CCustomEditListBox& list)
{
	for(int i=0;i<list.GetCount();i++)
	{
		CParameter* pParam = (CParameter*)list.GetItemData(i);
		delete pParam;
		pParam = NULL;
	}
}