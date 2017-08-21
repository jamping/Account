// UserAccountDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Account.h"
#include "UserAccountDlg.h"
#include "AccountManageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserAccountDlg dialog


CUserAccountDlg::CUserAccountDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserAccountDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserAccountDlg)
	m_strTotalMoney = _T("");
	//}}AFX_DATA_INIT
	m_nCurPage=1;
	m_nMaxPage=0;
}


void CUserAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserAccountDlg)
	DDX_Control(pDX, IDC_PREV_PAGE, m_btnPrevPage);
	DDX_Control(pDX, IDC_NEXT_PAGE, m_btnNextPage);
	DDX_Control(pDX, IDC_ADD_USER, m_btnAddUser);
	DDX_Text(pDX, IDC_TOTAL_MONEY, m_strTotalMoney);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserAccountDlg, CDialog)
	//{{AFX_MSG_MAP(CUserAccountDlg)
	ON_BN_CLICKED(IDC_PREV_PAGE, OnPrevPage)
	ON_BN_CLICKED(IDC_ADD_USER, OnAddUser)
	ON_BN_CLICKED(IDC_NEXT_PAGE, OnNextPage)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(IDC_PREV_PAGE,OnUpdatePrevPage)
	ON_UPDATE_COMMAND_UI(IDC_NEXT_PAGE,OnUpdateNextPage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserAccountDlg message handlers

BOOL CUserAccountDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here	
	ShowAccount(theApp.m_timeCur,theApp.GetAccountType());	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUserAccountDlg::OnPrevPage() 
{
	// TODO: Add your control notification handler code here
	m_nCurPage --;
	ShowAccount(theApp.m_timeCur,theApp.GetAccountType());
}

void CUserAccountDlg::OnAddUser() 
{
	// TODO: Add your control notification handler code here
	
	CAccount* pAccount = new CAccount;
	CAccountManageDlg dlg(pAccount);
	if(dlg.DoModal()==IDOK)
	{		
		pAccount->m_type = (CAccount::AccountType)(dlg.m_nAccountType+1);
		pAccount->m_strAccountName = dlg.m_strAccountName;
		pAccount->m_dwAccountBase = dlg.m_dwAccountBase;
        pAccount->SetID(pAccount->NewID(theApp.GetDB()));
		pAccount->SetDesc(pAccount->m_strAccountName);

		pAccount->SaveToDB(theApp.GetDB());

		theApp.SetAccount(pAccount);
		ShowAccount(theApp.m_timeCur,theApp.GetAccountType());

		MessageBox(_T("账户：")+pAccount->GetDesc()+_T("添加成功！"));
	}
	else
	{
		delete pAccount;
		pAccount = NULL;
	}
}

void CUserAccountDlg::OnNextPage() 
{
	// TODO: Add your control notification handler code here
	m_nCurPage ++;
	ShowAccount(theApp.m_timeCur,theApp.GetAccountType());
}

BOOL CUserAccountDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateDialogControls(this,FALSE);

	return CDialog::PreTranslateMessage(pMsg);
}
void CUserAccountDlg::OnUpdatePrevPage(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_nCurPage > 1);
}
void CUserAccountDlg::OnUpdateNextPage(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_nCurPage < m_nMaxPage);
}


void CUserAccountDlg::ShowAccount(COleDateTime timeCur,int nAccountType /* =0 */)
{
	int nIndex=0;
    //Delete the old account buttons
	while ( m_btn[nIndex].GetSafeHwnd() )
	{
		m_btn[nIndex++].DestroyWindow();
	}

	int nTotal = theApp.GetAccountList(nAccountType).GetSize();
	
	m_nMaxPage = nTotal / (ACCOUNT_X*ACCOUNT_Y);
		if( nTotal % (ACCOUNT_X*ACCOUNT_Y) !=0 )
			m_nMaxPage += 1;	

    if(nTotal > 0)
	{		
		//Show the news account buttons
		CString str;
		CRect rect,rect1,rect2;	
		
		rect = CRect(10,10,160,80);
		
		nIndex = (m_nCurPage-1)*(ACCOUNT_X*ACCOUNT_Y);    		
		int nBtn = 0;
		for(int i=0;i<ACCOUNT_Y;i++)
		{
			if( nIndex >= nTotal )
				break;
			
			rect1 = rect;
			rect1.OffsetRect(0,i*rect.Height()+i*10);
			
			for(int j=0;j<ACCOUNT_X;j++)
			{
				if( nIndex >= nTotal )
					break;
				
				CAccount* pAccount = theApp.GetAccountList(nAccountType).GetAt(nIndex);
				
				pAccount->ComputerMoney(timeCur);
				
				rect2 = rect1;
				rect2.OffsetRect(j*rect.Width()+j*10,0);            
				
				m_btn[nBtn].SetAccount(pAccount);
				m_btn[nBtn++].Create(rect2,this,nIndex++);
			}
		} 
	}
	//computer the total money
	double dwTotal = 0.0;
	for(int i=0; i< nTotal ;i++)
	{
         dwTotal += theApp.GetAccountList(nAccountType).GetAt(i)->m_dwAccountLeft;
	}
	m_strTotalMoney.Format("总金额：%.02f",dwTotal);

    UpdateData(FALSE);
}
