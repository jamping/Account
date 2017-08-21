// SearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Account.h"
#include "SearchDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg dialog


CSearchDlg::CSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchDlg)
	m_strCustomer = _T("");
	m_strRemark = _T("");
	m_time1 = COleDateTime::GetCurrentTime();
	m_time2 = COleDateTime::GetCurrentTime();
	m_bTime = FALSE;
	//}}AFX_DATA_INIT
}


void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchDlg)
	DDX_Control(pDX, IDC_CUSTOMER, m_comboCustomer);
	DDX_CBString(pDX, IDC_CUSTOMER, m_strCustomer);
	DDX_Text(pDX, IDC_REMARK, m_strRemark);
	DDX_DateTimeCtrl(pDX, IDC_TIME1, m_time1);
	DDX_DateTimeCtrl(pDX, IDC_TIME2, m_time2);
	DDX_Check(pDX, IDC_CHECK_TIME, m_bTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchDlg)
	ON_BN_CLICKED(IDC_CHECK_TIME, OnCheckTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg message handlers

BOOL CSearchDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString str;

	CADORecordset rs(theApp.GetDB());
	if(rs.Open(_T("select ParameterValue from Parameter where ParameterType=4"),CADORecordset::openQuery))
	{
         while (!rs.IsEOF())
         {
			 rs.GetFieldValue(_T("ParameterValue"),str);
			 m_comboCustomer.AddString(str);

			 rs.MoveNext();
         }
		 rs.Close();
	}
	COleDateTime timeMoreMonth,curTime = COleDateTime::GetCurrentTime();
	m_time1.SetDate(curTime.GetYear(),curTime.GetMonth(),1);
	if(curTime.GetMonth() == 12)
        timeMoreMonth.SetDate(curTime.GetYear()+1,1,1);
	else
	    timeMoreMonth.SetDate(curTime.GetYear(),curTime.GetMonth()+1,1);

	m_time2 = timeMoreMonth-COleDateTimeSpan(1,0,0,0);

	GetDlgItem(IDC_TIME1)->EnableWindow(m_bTime);
	GetDlgItem(IDC_TIME2)->EnableWindow(m_bTime);

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSearchDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CSearchDlg::OnCheckTime() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	GetDlgItem(IDC_TIME1)->EnableWindow(m_bTime);
	GetDlgItem(IDC_TIME2)->EnableWindow(m_bTime);
	
	m_bTime = !m_bTime; 
}
