// MoneyMoveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Account.h"
#include "MoneyMoveDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMoneyMoveDlg dialog


CMoneyMoveDlg::CMoneyMoveDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMoneyMoveDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMoneyMoveDlg)
	m_dwMoney = 0.0;
	m_strRemark = _T("");
	m_time = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	m_pAccountSrc = NULL;
	m_pAccountDst = NULL;
}


void CMoneyMoveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMoneyMoveDlg)
	DDX_Control(pDX, IDC_MONEY, m_editMoney);
	DDX_Control(pDX, IDC_ACCOUNT2, m_comboAccount2);
	DDX_Control(pDX, IDC_ACCOUNT1, m_comboAccount1);
	DDX_Text(pDX, IDC_MONEY, m_dwMoney);
	DDX_Text(pDX, IDC_REMARK, m_strRemark);
	DDX_DateTimeCtrl(pDX, IDC_TIME, m_time);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMoneyMoveDlg, CDialog)
	//{{AFX_MSG_MAP(CMoneyMoveDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMoneyMoveDlg message handlers

BOOL CMoneyMoveDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_editMoney.EnableCalculatorButton ();
    m_editMoney.DisableMask();					// Don't use the mask
	m_editMoney.SetValidChars(_T("1234567890."));	// Valid string characters 

	int nSel = 0;
	for(int i=0;i<theApp.GetAccountList(theApp.GetAccountType()).GetSize();i++)
	{
		CAccount* pAccount = theApp.GetAccountList(theApp.GetAccountType()).GetAt(i);
		int nIndex = m_comboAccount1.AddString(pAccount->GetDesc());

		m_comboAccount2.AddString(pAccount->GetDesc());
		m_comboAccount1.SetItemData(nIndex,(DWORD)pAccount);
		m_comboAccount2.SetItemData(nIndex,(DWORD)pAccount);
        
		if( m_pAccountSrc && m_pAccountSrc->GetID()==pAccount->GetID())
			m_comboAccount1.SetCurSel(nIndex);
	}
	
    
	if(m_pAccountSrc!=NULL)
	{
		m_comboAccount1.EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMoneyMoveDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();

	int nIndex = m_comboAccount1.GetCurSel();
	if(nIndex!=-1)
	{
         m_pAccountSrc = (CAccount*)m_comboAccount1.GetItemData(nIndex);
	}
	else
	{
	    MessageBox(_T("请选择调出账户"));
		return;
	}
	nIndex = m_comboAccount2.GetCurSel();
	if(nIndex!=-1)
	{
         m_pAccountDst= (CAccount*)m_comboAccount1.GetItemData(nIndex);
	}
	else
	{
	    MessageBox(_T("请选择调入账户"));
		return;
	}
	if(m_pAccountSrc->GetID() == m_pAccountDst->GetID())
	{
        MessageBox(_T("调入账户不能与调出账户相同"),_T("错误"),MB_OK|MB_ICONWARNING);
		return;
	}
	if(m_dwMoney == 0.)
	{
		MessageBox(_T("金额不能为0"),_T("错误"),MB_OK|MB_ICONWARNING);
		return;
	}

	CDialog::OnOK();
}
