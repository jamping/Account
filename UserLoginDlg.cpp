// UserLoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Account.h"
#include "UserLoginDlg.h"
#include "AccountDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserLoginDlg dialog


CUserLoginDlg::CUserLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserLoginDlg)
	m_strPassWord = _T("");
	m_strUserName = _T("");
	//}}AFX_DATA_INIT
}


void CUserLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserLoginDlg)
	DDX_Control(pDX, IDC_USERNAME, m_ctlUserName);
	DDX_Control(pDX, IDC_LOGIN, m_btnLogin);
	DDX_Text(pDX, IDC_PASSWORD, m_strPassWord);
	DDX_Text(pDX, IDC_USERNAME, m_strUserName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CUserLoginDlg)
	ON_BN_CLICKED(IDC_LOGIN, OnLogin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserLoginDlg message handlers

BOOL CUserLoginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_btnLogin.SetImage(IDB_KEY);
	m_btnLogin.SizeToContent();
	
    m_ctlUserName.SetCurSel(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUserLoginDlg::OnLogin() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
    GetDlgItem(IDC_PASSWORD)->SetWindowText(_T(""));
	
	CAccountDlg* pMainDlg = (CAccountDlg*)AfxGetMainWnd();

	for(int i=1;i<7;i++)
		pMainDlg->m_wndTab.ShowTab(i,FALSE);

	int nIndex = m_ctlUserName.GetCurSel();
	if(nIndex != -1)
	{
		CUser* pUser = (CUser*)theApp.GetUser(nIndex);
		if(m_strPassWord.Compare(pUser->GetPassWord())!=0)
		{
			MessageBox(_T("ÃÜÂë²»ÕýÈ·"),_T("´íÎó"),MB_OK|MB_ICONWARNING);
			return;
		}
	}
	switch(nIndex)
	{
	case 0:
		{			
            for(i=5;i<7;i++)
	            pMainDlg->m_wndTab.ShowTab(i,TRUE);
         
			pMainDlg->m_wndTab.SetActiveTab(5);
		}
		break;
	case 1:
		{			
			for(i=1;i<5;i++)
	            pMainDlg->m_wndTab.ShowTab(i,TRUE);	

			pMainDlg->m_wndTab.SetActiveTab(1);
		}
		break;
	}
	
	pMainDlg->Init(nIndex+1);

}
void CUserLoginDlg::OnOK()
{
	OnLogin();
}