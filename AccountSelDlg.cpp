// AccountSelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Account.h"
#include "AccountSelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAccountSelDlg dialog


CAccountSelDlg::CAccountSelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAccountSelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAccountSelDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nType = 0;
}


void CAccountSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAccountSelDlg)
	DDX_Control(pDX, IDC_BUTTON_ACCOUNT3, m_btn3);
	DDX_Control(pDX, IDC_BUTTON_ACCOUNT2, m_btn2);
	DDX_Control(pDX, IDC_BUTTON_ACCOUNT, m_btn1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAccountSelDlg, CDialog)
	//{{AFX_MSG_MAP(CAccountSelDlg)
	ON_BN_CLICKED(IDC_BUTTON_ACCOUNT, OnButtonAccount)
	ON_BN_CLICKED(IDC_BUTTON_ACCOUNT2, OnButtonAccount2)
	ON_BN_CLICKED(IDC_BUTTON_ACCOUNT3, OnButtonAccount3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAccountSelDlg message handlers

void CAccountSelDlg::OnButtonAccount() 
{
	// TODO: Add your control notification handler code here
	m_nType = 0;

	CDialog::OnOK();
}

void CAccountSelDlg::OnButtonAccount2() 
{
	// TODO: Add your control notification handler code here
	m_nType = 1;
	CDialog::OnOK();
}

void CAccountSelDlg::OnButtonAccount3() 
{
	// TODO: Add your control notification handler code here
	m_nType = 2;
	CDialog::OnOK();
}

BOOL CAccountSelDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_btn1.SetImage(IDB_COMPANY_ACCOUNT);
	m_btn1.SetWindowText("");
	m_btn1.SizeToContent();
	m_btn2.SetImage(IDB_COMPANY_ACCOUNT2);
	m_btn2.SetWindowText("");
	m_btn2.SizeToContent();
	m_btn3.SetImage(IDB_COMPANY_ACCOUNT3);
	m_btn3.SetWindowText("");
	m_btn3.SizeToContent();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
