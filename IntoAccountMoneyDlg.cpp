// IntoAccountMoneyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Account.h"
#include "IntoAccountMoneyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIntoAccountMoneyDlg dialog


CIntoAccountMoneyDlg::CIntoAccountMoneyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIntoAccountMoneyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIntoAccountMoneyDlg)
	m_dwMoney = 0.0;
	//}}AFX_DATA_INIT
}


void CIntoAccountMoneyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIntoAccountMoneyDlg)
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_MONEY, m_editMoney);
	DDX_Text(pDX, IDC_MONEY, m_dwMoney);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIntoAccountMoneyDlg, CDialog)
	//{{AFX_MSG_MAP(CIntoAccountMoneyDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIntoAccountMoneyDlg message handlers

BOOL CIntoAccountMoneyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_editMoney.EnableCalculatorButton ();
    m_editMoney.DisableMask();					// Don't use the mask
	m_editMoney.SetValidChars(_T("1234567890."));	// Valid string characters 
	m_btnOk.SetImage(IDB_OK);
	m_btnCancel.SetImage(IDB_CANCEL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CIntoAccountMoneyDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();

	if(m_dwMoney == 0.)
	{
		MessageBox(_T("金额不能为0"),_T("错误"),MB_OK|MB_ICONWARNING);
		return;
	}
	CDialog::OnOK();
}
