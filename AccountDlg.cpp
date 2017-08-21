// AccountDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Account.h"
#include "AccountDlg.h"
#include "AccountSelDlg.h"
#include "MoneyDlg.h"
#include "MoneyOper.h"
#include "MoneyMoveDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAccountDlg dialog

CAccountDlg::CAccountDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAccountDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAccountDlg)
	m_strCurUser = _T("");
	m_time = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAccountDlg)
	DDX_Control(pDX, IDC_PREV_DATE, m_btnPrevDate);
	DDX_Control(pDX, IDC_NEXT_DATE, m_btnNextDate);
	DDX_Control(pDX, IDC_OUTCOME, m_btnOutcome);
	DDX_Control(pDX, IDC_INCOME, m_btnIncome);
	DDX_Control(pDX, IDC_BANLANCE, m_btnBanlance);
	DDX_Control(pDX, IDC_BACKUP, m_btnBackup);
	DDX_Control(pDX, IDC_ACCOUNT_SCOPE, m_btnAccountScope);
	DDX_Control(pDX, IDC_TAB, m_tabLoc);
	DDX_Text(pDX, IDC_CUR_USER, m_strCurUser);
	DDX_DateTimeCtrl(pDX, IDC_SEL_DATE, m_time);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAccountDlg, CDialog)
	//{{AFX_MSG_MAP(CAccountDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PREV_DATE, OnPrevDate)
	ON_BN_CLICKED(IDC_NEXT_DATE, OnNextDate)
	ON_BN_CLICKED(IDC_ACCOUNT_SCOPE, OnAccountScope)
	ON_BN_CLICKED(IDC_INCOME, OnIncome)
	ON_BN_CLICKED(IDC_OUTCOME, OnOutcome)
	ON_BN_CLICKED(IDC_BANLANCE, OnBanlance)
	ON_BN_CLICKED(IDC_BACKUP, OnBackup)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_SEL_DATE, OnDatetimechangeSelDate)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_UPDATE_INFO,OnUpdateInfo)
	ON_UPDATE_COMMAND_UI(IDC_INCOME,OnUpdateIncome)
	ON_UPDATE_COMMAND_UI(IDC_OUTCOME,OnUpdateOutcome)
	ON_UPDATE_COMMAND_UI(IDC_BANLANCE,OnUpdateBalance)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAccountDlg message handlers

BOOL CAccountDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	theApp.m_timeCur = m_time;

	CRect rectTab;

	m_tabLoc.GetWindowRect (&rectTab);
	ScreenToClient (&rectTab);

	m_wndTab.Create(CBCGPTabWnd::STYLE_3D,rectTab,this,CBCGPTabWnd::LOCATION_TOP);
    m_wndTab.SetImageList (IDB_TAB, 32, RGB (255, 255, 255));
   
	m_dlgLogin.Create(CUserLoginDlg::IDD,&m_wndTab);
	m_dlgUserAccount.Create(CUserAccountDlg::IDD,&m_wndTab);
	m_dlgAccountLog.Create(CAccountLogDlg::IDD,&m_wndTab);
	m_dlgInOut.Create(CInOutDlg::IDD,&m_wndTab);
	m_dlgReport.Create(CReportDlg::IDD,&m_wndTab);
	m_dlgSetting.Create(CSettingDlg::IDD,&m_wndTab);
	m_dlgDataManage.Create(CDataManageDlg::IDD,&m_wndTab);	

	m_wndTab.AddTab(&m_dlgLogin, "用户登陆", 0, FALSE);
	m_wndTab.AddTab(&m_dlgUserAccount, "账户状况", 1, FALSE);
	m_wndTab.AddTab(&m_dlgAccountLog, "日记账簿", 2, FALSE);
	m_wndTab.AddTab(&m_dlgInOut, "应收应付", 3, FALSE);
	m_wndTab.AddTab(&m_dlgReport, "报表中心", 4, FALSE); 
	m_wndTab.AddTab(&m_dlgSetting, "软件设置", 5, FALSE); 
	m_wndTab.AddTab(&m_dlgDataManage, "数据维护", 6, FALSE); 
	
	for(int i=1;i<7;i++)
	   m_wndTab.ShowTab(i,FALSE);

	m_wndTab.SetLocation (CBCGPTabWnd::LOCATION_TOP);
	m_wndTab.RecalcLayout ();
	m_wndTab.RedrawWindow ();
	m_wndTab.SetActiveTab(0);

	m_btnAccountScope.SetImage(IDB_EMPTY_ACCOUNT);
	m_btnAccountScope.SetWindowText("");
	m_btnAccountScope.SizeToContent();

	m_btnPrevDate.SetImage(IDB_PREV);
	m_btnPrevDate.SetWindowText("");
	m_btnPrevDate.SizeToContent();

	m_btnNextDate.SetImage(IDB_NEXT);
	m_btnNextDate.SetWindowText("");	
	m_btnNextDate.SizeToContent();

	m_btnIncome.SetImage(IDB_MONEY_IN);
	m_btnIncome.SizeToContent();
	
	m_btnOutcome.SetImage(IDB_MONEY_OUT);
	m_btnOutcome.SizeToContent();
	
	m_btnBanlance.SetImage(IDB_MONEY_DRAW);
	m_btnBanlance.SizeToContent();

	m_btnBackup.SetImage(IDB_BACKUP);
	m_btnBackup.m_bTopImage=TRUE;
	m_btnBackup.SizeToContent();

	Init();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAccountDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAccountDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAccountDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CAccountDlg::OnPrevDate() 
{
	// TODO: Add your control notification handler code here
	m_time -= COleDateTimeSpan(1,0,0,0);
	theApp.m_timeCur = m_time;
	m_dlgUserAccount.ShowAccount(theApp.m_timeCur,theApp.GetAccountType());
    m_dlgAccountLog.ShowMoneyOper(theApp.m_timeCur,theApp.GetAccountType());

	UpdateData(FALSE);
}

void CAccountDlg::OnNextDate() 
{
	// TODO: Add your control notification handler code here
	m_time += COleDateTimeSpan(1,0,0,0);
	theApp.m_timeCur = m_time;
	m_dlgUserAccount.ShowAccount(theApp.m_timeCur,theApp.GetAccountType());
	m_dlgAccountLog.ShowMoneyOper(theApp.m_timeCur,theApp.GetAccountType());

	UpdateData(FALSE);
}

void CAccountDlg::OnAccountScope() 
{
	// TODO: Add your control notification handler code here
	CAccountSelDlg dlg;
	if( dlg.DoModal()==IDOK )
	{
		theApp.SetAccountType(dlg.GetAccountType());
        switch(theApp.GetAccountType())
        {
		case 0:
			m_btnAccountScope.SetImage(IDB_COMPANY_ACCOUNT);
			break;
		case 1:
			m_btnAccountScope.SetImage(IDB_COMPANY_ACCOUNT2);
			break;
		case 2:
			m_btnAccountScope.SetImage(IDB_COMPANY_ACCOUNT3);
			break;
        }
		m_btnAccountScope.Invalidate();

		OnUpdateInfo();
	}
}

void CAccountDlg::OnIncome() 
{
	// TODO: Add your control notification handler code here
	CMoneyDlg dlg(CMoneyDlg::NEW_GET);
    dlg.m_timeInput = theApp.m_timeCur;

	if(dlg.DoModal()==IDOK)
	{
		CMoneyOper* pMoney = new CMoneyOper;
        pMoney->SetID(pMoney->NewID(theApp.GetDB()));

		dlg.GetValue(pMoney);		
		BOOL bRet = pMoney->SaveToDB(theApp.GetDB());
		if(bRet)
		{
			OnUpdateInfo();
		}
		MessageBox(bRet?_T("记录添加成功！"):_T("记录添加失败！"));

	}
}

void CAccountDlg::OnOutcome() 
{
	// TODO: Add your control notification handler code here
	CMoneyDlg dlg(CMoneyDlg::NEW_PAY);
	dlg.m_timeInput = theApp.m_timeCur;
	
	if(dlg.DoModal()==IDOK)
	{
		CMoneyOper* pMoney = new CMoneyOper;
        pMoney->SetID(pMoney->NewID(theApp.GetDB()));

		dlg.GetValue(pMoney);		
		BOOL bRet = pMoney->SaveToDB(theApp.GetDB());
		if(bRet)
		{
			OnUpdateInfo();
		}
		MessageBox(bRet?_T("记录添加成功！"):_T("记录添加失败！"));

	}
}

void CAccountDlg::OnBanlance() 
{
	// TODO: Add your control notification handler code here
	CMoneyMoveDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
         CAccount* pAccountSrc = dlg.m_pAccountSrc;
		 CAccount* pAccountDst = dlg.m_pAccountDst;

         CMoneyOper* pMoneyOut = new CMoneyOper;
		 pMoneyOut->SetID(pMoneyOut->NewID(theApp.GetDB()));
		 pMoneyOut->AddTo(pAccountSrc);

		 pMoneyOut->m_dwMoneyOut = dlg.m_dwMoney;
		 pMoneyOut->m_dwMoneySum = -dlg.m_dwMoney;
		 pMoneyOut->m_timeCreate.SetDate(dlg.m_time.GetYear(),dlg.m_time.GetMonth(),dlg.m_time.GetDay());
		 pMoneyOut->m_timeRecord.SetDate(dlg.m_time.GetYear(),dlg.m_time.GetMonth(),dlg.m_time.GetDay());
		 pMoneyOut->m_strMoneyUser = _T("调出=>")+pAccountDst->GetDesc();
         pMoneyOut->m_strMoneyRemark = dlg.m_strRemark;
		 
		 pMoneyOut->SaveToDB(theApp.GetDB());

         CMoneyOper* pMoneyIn = new CMoneyOper;
		 pMoneyIn->SetID(pMoneyIn->NewID(theApp.GetDB()));
		 pMoneyIn->AddTo(pAccountDst);

		 pMoneyIn->m_dwMoneyIn = dlg.m_dwMoney;
		 pMoneyIn->m_dwMoneySum = dlg.m_dwMoney;
		 pMoneyIn->m_timeCreate.SetDate(dlg.m_time.GetYear(),dlg.m_time.GetMonth(),dlg.m_time.GetDay());
		 pMoneyIn->m_timeRecord.SetDate(dlg.m_time.GetYear(),dlg.m_time.GetMonth(),dlg.m_time.GetDay());
		 pMoneyIn->m_strMoneyUser = pAccountSrc->GetDesc()+_T("=>调入");
         pMoneyIn->m_strMoneyRemark = dlg.m_strRemark;
		 
		 pMoneyIn->SaveToDB(theApp.GetDB());

		 OnUpdateInfo();

         MessageBox(_T("账户平调成功！"));
	}
}

void CAccountDlg::OnBackup() 
{
	// TODO: Add your control notification handler code here	
	CFileDialog fileDlg(FALSE,"mdb",COleDateTime::GetCurrentTime().Format("%Y-%m-%d.mdb"),
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY,"Microsoft Access 数据库(*.mdb)|*.mdb||");
	
	BOOL bRet = FALSE;

	if(fileDlg.DoModal()==IDOK)
	{		
		CString srcFile = _T("");
		char path[256];
		
		::GetModuleFileName(NULL,path,256);

		srcFile=(CString)path;
		srcFile=srcFile.Left(srcFile.ReverseFind('\\')+1)+"Account.mdb";

		bRet = CopyFile(srcFile,fileDlg.GetPathName(),FALSE);
	}
	MessageBox(bRet?_T("数据备份成功!"):_T("数据备份失败!"));
}
void CAccountDlg::Init(UINT nValue /* = 0  */)
{
	BOOL bEnable = TRUE;

	switch(nValue)
	{
	case 0:
		m_strCurUser = _T("未登陆");
		bEnable = FALSE;
		break;
	case 1:
		m_strCurUser = _T("管理员");
		bEnable = FALSE;
		break;
	case 2:
		m_strCurUser = _T("出纳");
		break;
	}	

	m_btnAccountScope.EnableWindow(bEnable);
	GetDlgItem(IDC_SEL_DATE)->EnableWindow(bEnable);
	m_btnPrevDate.EnableWindow(bEnable);
	m_btnNextDate.EnableWindow(bEnable);
	m_btnIncome.EnableWindow(bEnable);
	m_btnOutcome.EnableWindow(bEnable);
	m_btnBanlance.EnableWindow(bEnable);
	m_btnBackup.EnableWindow(bEnable);	

	if(bEnable)
	{
		m_btnAccountScope.SetImage(IDB_COMPANY_ACCOUNT);
		m_btnAccountScope.Invalidate();
	}

	UpdateData(FALSE);

}

void CAccountDlg::OnDatetimechangeSelDate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NMDATETIMECHANGE* pDateTime =(LPNMDATETIMECHANGE) pNMHDR; 
	m_time = COleDateTime(pDateTime->st);

	theApp.m_timeCur = m_time;
	OnUpdateInfo();
	UpdateData(FALSE);

	*pResult = 0;
}
void CAccountDlg::OnUpdateInfo()
{
    m_dlgUserAccount.ShowAccount(theApp.m_timeCur,theApp.GetAccountType());
	m_dlgAccountLog.ShowMoneyOper(theApp.m_timeCur,theApp.GetAccountType());
}

BOOL CAccountDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateDialogControls(this,FALSE);

	return CDialog::PreTranslateMessage(pMsg);
}
void CAccountDlg::OnUpdateIncome(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_strCurUser.Compare(_T("出纳")) ==0 && theApp.GetAccountList(theApp.GetAccountType()).GetSize()>0);
}
void CAccountDlg::OnUpdateOutcome(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_strCurUser.Compare(_T("出纳")) ==0 && theApp.GetAccountList(theApp.GetAccountType()).GetSize()>0);
}
void CAccountDlg::OnUpdateBalance(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_strCurUser.Compare(_T("出纳")) ==0 && theApp.GetAccountList(theApp.GetAccountType()).GetSize()>1);
}

void CAccountDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if( MessageBox(_T("是否退出系统？"),_T("请确认"),MB_YESNO|MB_ICONQUESTION) == IDNO )
		return ;
	
	CDialog::OnClose();
}
