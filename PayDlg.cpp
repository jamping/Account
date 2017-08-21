// PayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Account.h"
#include "PayDlg.h"
#include "IntoAccountMoneyDlg.h"
#include "MoneyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPayDlg dialog


CPayDlg::CPayDlg(PayDlgType type,CWnd* pParent /* = NULL */)
	: CDialog(CPayDlg::IDD, pParent),m_type(type)
{
	//{{AFX_DATA_INIT(CPayDlg)
	m_strCustomer = _T("");
	m_dwGetMoney = 0.0;
	m_dwGettedMoney = 0.0;
	m_dwLeftMoney = 0.0;
	m_strRemark = _T("");
	m_strGetPay = _T("应收金额");
	m_strGettedPay = _T("已收金额");
	m_time = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void CPayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPayDlg)
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_GETPAY_INTO_ACCOUNT, m_btnIntoAccount);
	DDX_Control(pDX, IDC_GET_MONEY, m_btnMoney);
	DDX_Control(pDX, IDC_PIC, m_pic);
	DDX_Control(pDX, IDC_CUSTOMER, m_comboCustomer);
	DDX_CBString(pDX, IDC_CUSTOMER, m_strCustomer);
	DDX_Text(pDX, IDC_GET_MONEY, m_dwGetMoney);
	DDX_Text(pDX, IDC_GETTED_MONEY, m_dwGettedMoney);
	DDX_Text(pDX, IDC_LEFT_MONEY, m_dwLeftMoney);
	DDX_Text(pDX, IDC_REMARK, m_strRemark);
	DDX_Text(pDX, IDC_STATIC_GETPAY, m_strGetPay);
	DDX_Text(pDX, IDC_STATIC_GETTED_PAY, m_strGettedPay);
	DDX_DateTimeCtrl(pDX, IDC_TIME, m_time);
	//}}AFX_DATA_MAP
}
void CPayDlg::GetValue(CPay * pPay)
{	
    pPay->m_timePay.SetDate(m_time.GetYear(),m_time.GetMonth(),m_time.GetDay());
	pPay->m_strCustomer = m_strCustomer;
    pPay->m_dwPaySum = m_dwGetMoney;
    pPay->m_dwPayedSum = m_dwGettedMoney;
	m_dwLeftMoney = m_dwGetMoney-m_dwGettedMoney;
	pPay->m_dwPayLeft = m_dwLeftMoney; 
	pPay->m_strPayRemark = m_strRemark;

	if(m_type>=NEW_PAY)
	{
        pPay->m_dwPaySum = -pPay->m_dwPaySum;
        pPay->m_dwPayedSum = -pPay->m_dwPayedSum;
	    pPay->m_dwPayLeft = -pPay->m_dwPayLeft; 
	}
}
void CPayDlg::SetValue(const CPay* pPay)
{
    m_time = pPay->m_timePay;
	m_strCustomer = pPay->m_strCustomer;		
	m_dwGetMoney = pPay->m_dwPaySum;
	m_dwGettedMoney = pPay->m_dwPayedSum;
	m_dwLeftMoney = pPay->m_dwPayLeft;
	m_strRemark = pPay->m_strPayRemark;

	if(m_type>=NEW_PAY)
	{
        m_dwGetMoney = -m_dwGetMoney;
		m_dwGettedMoney = -m_dwGettedMoney;
		m_dwLeftMoney = -m_dwLeftMoney;		
	}
}

BEGIN_MESSAGE_MAP(CPayDlg, CDialog)
	//{{AFX_MSG_MAP(CPayDlg)
	ON_BN_CLICKED(IDC_SAVE_CUSTOMER, OnSaveCustomer)
	ON_BN_CLICKED(IDC_GETPAY_INTO_ACCOUNT, OnGetpayIntoAccount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPayDlg message handlers

void CPayDlg::OnSaveCustomer() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	if(m_strCustomer.IsEmpty())
	{
		MessageBox("客户名称不能为空！","错误",MB_OK|MB_ICONWARNING);
		return ;
	}
	CString strSql,str;
	BOOL bRet = TRUE;
	strSql.Format("select * from Parameter where ParameterValue='%s' and ParameterType=%d",m_strCustomer,4);

	CADORecordset rs(theApp.GetDB());
	bRet = rs.Open(strSql,CADORecordset::openQuery);
	if(bRet)
	{
		if(rs.GetRecordCount()==0)
		{
			bRet &= rs.AddNew();
			bRet &= rs.SetFieldValue("ParameterType",4);
			bRet &= rs.SetFieldValue("ParameterValue",m_strCustomer);
			bRet &= rs.Update();

			m_comboCustomer.AddString(m_strCustomer);
		}
		rs.Close();
	}

	MessageBox(bRet ? _T("客户添加成功！"):_T("客户添加失败！"));
}

void CPayDlg::OnGetpayIntoAccount() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	CIntoAccountMoneyDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
         if(dlg.m_dwMoney > m_dwLeftMoney)
		 {
			 MessageBox(_T("输入金额大于尚欠金额，请重新操作！"),_T("错误"),MB_OK|MB_ICONWARNING);
			 return;
		 }
		 CMoneyDlg dlg1((m_type>=NEW_PAY)?CMoneyDlg::NEW_PAY:CMoneyDlg::NEW_GET);
		 dlg1.m_timeInput = theApp.m_timeCur;
		 dlg1.m_dwMoney = dlg.m_dwMoney;
		 dlg1.m_strCustomerName = m_strCustomer;
		 dlg1.m_strRemark = m_strRemark;

		 if(dlg1.DoModal()==IDOK)
		 {
			 CMoneyOper* pMoney = new CMoneyOper;
			 pMoney->SetID(pMoney->NewID(theApp.GetDB()));
			 
			 dlg1.GetValue(pMoney);	
			 
			 BOOL bRet = pMoney->SaveToDB(theApp.GetDB());
			 if(bRet)
			 {
				 AfxGetMainWnd()->SendMessage(WM_UPDATE_INFO);
				 m_dwGettedMoney += dlg.m_dwMoney;
				 m_dwLeftMoney -= dlg.m_dwMoney;
				 
				 UpdateData(FALSE);
			 }
			 MessageBox(bRet?_T("记录添加成功！"):_T("记录添加失败！"));
			 
		 }
	}
}

BOOL CPayDlg::OnInitDialog() 
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

	m_btnMoney.EnableCalculatorButton ();
    m_btnMoney.DisableMask();					// Don't use the mask
	m_btnMoney.SetValidChars(_T("1234567890."));	// Valid string characters 
    
	m_btnOk.SetImage(IDB_OK);
	m_btnCancel.SetImage(IDB_CANCEL);
	m_btnIntoAccount.SetImage(IDB_TWOSIDE);
	
	UINT nID = 0;
	switch(m_type)
	{
	case NEW_GET:
		nID = IDB_NEW_GET2;
		m_btnIntoAccount.ShowWindow(FALSE);
		break;
	case EDIT_GET:
		nID = IDB_EDIT_GET2;
		break;
	case NEW_PAY:
		nID = IDB_NEW_PAY2;	
		m_btnIntoAccount.ShowWindow(FALSE);
		break;
	case EDIT_PAY:
		nID = IDB_EDIT_PAY2;
		break;
	}	
    CBitmap bmp;
	bmp.LoadBitmap(nID);
 	BITMAP bmpobj;
 	bmp.GetBitmap(&bmpobj);

	m_pic.SetBitmap(nID,bmpobj.bmWidth);
    DeleteObject(HBITMAP(&bmpobj));

    if(m_type>EDIT_GET)
	{
		m_strGetPay = _T("应付金额");
		m_strGettedPay = _T("已付金额");
		m_btnIntoAccount.SetWindowText(_T("应付入账"));
	}
    static_cast<CEdit*>(GetDlgItem(IDC_GETTED_MONEY))->SetReadOnly();
    static_cast<CEdit*>(GetDlgItem(IDC_LEFT_MONEY))->SetReadOnly();

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPayDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();

	if(m_dwGetMoney == 0.)
	{
		MessageBox(_T("金额不能为0"),_T("错误"),MB_OK|MB_ICONWARNING);
		return;
	}

	CDialog::OnOK();
}
