// AccountManageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Account.h"
#include "AccountManageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAccountManageDlg dialog


CAccountManageDlg::CAccountManageDlg(CAccount* pAccount,CWnd* pParent /* = NULL */)
	: CDialog(CAccountManageDlg::IDD, pParent),m_pAccount(pAccount)
{
	//{{AFX_DATA_INIT(CAccountManageDlg)
	m_strAccountName = _T("");
	m_dwAccountBase = 0.0;
	m_nAccountType = 0;
	//}}AFX_DATA_INIT
}


void CAccountManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAccountManageDlg)
	DDX_Text(pDX, IDC_ACCOUNT_NAME, m_strAccountName);
	DDX_Text(pDX, IDC_MONEY_BASE, m_dwAccountBase);
	DDX_Radio(pDX, IDC_RADIO_BANK, m_nAccountType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAccountManageDlg, CDialog)
	//{{AFX_MSG_MAP(CAccountManageDlg)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAccountManageDlg message handlers

BOOL CAccountManageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(m_pAccount->GetID() == 0)
	{
		SetWindowText(_T("新建账户"));
		GetDlgItem(IDC_DEL)->ShowWindow(FALSE);
	}
	else
	{
		SetWindowText(_T("修改账户"));
	}
	if(m_pAccount!=NULL)
	{
		m_strAccountName = m_pAccount->GetDesc();
		m_dwAccountBase = m_pAccount->m_dwAccountBase;
		m_nAccountType = (int)m_pAccount->m_type;
		m_nAccountType -=1;
	}
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAccountManageDlg::OnDel() 
{
	// TODO: Add your control notification handler code here
	CString str;
	str.Format("确实要删除账户：%s所有数据吗？",m_pAccount->GetDesc());

	if(MessageBox(str,_T("请确认"),MB_YESNO) == IDNO)
		return;

	if(m_pAccount!=NULL)
	{
		if(m_pAccount->DeleteFromDB(theApp.GetDB()))
		{
			int i = 0;
			
			for(i=0;i<theApp.GetAccountList(m_pAccount->m_type).GetSize();i++)
			{
				CAccount* pAccount = theApp.GetAccountList(m_pAccount->m_type).GetAt(i);
				if(m_pAccount->GetID() == pAccount->GetID())
				{
					theApp.GetAccountList(m_pAccount->m_type).RemoveAt(i);
					break;
				}
			}
			
			
			for(i=0;i<theApp.GetAccountList().GetSize();i++)
			{
				 CAccount* pAccount = theApp.GetAccountList().GetAt(i);
				 if(m_pAccount->GetID() == pAccount->GetID())
				 {
                      theApp.GetAccountList().RemoveAt(i);

					  delete m_pAccount;
					  m_pAccount = NULL;
					  break;
				 }
			}
			AfxGetMainWnd()->SendMessage(WM_UPDATE_INFO);
		}

	}
	CDialog::OnCancel();
}

void CAccountManageDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
    if(m_strAccountName.IsEmpty())
	{
		MessageBox(_T("账户名不能为空！"),_T("错误"),MB_OK|MB_ICONWARNING);
		return;
	}
	m_pAccount->m_type = CAccount::AccountType(m_nAccountType+1);
	m_pAccount->m_strAccountName = m_strAccountName;
	m_pAccount->m_dwAccountBase = m_dwAccountBase;
    m_pAccount->SetDesc(m_strAccountName);
	
	CDialog::OnOK();
}
