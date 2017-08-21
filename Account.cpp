// Account.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Account.h"
#include "AccountDlg.h"
#include "MoneyOper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAccountApp

BEGIN_MESSAGE_MAP(CAccountApp, CWinApp)
	//{{AFX_MSG_MAP(CAccountApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAccountApp construction

CAccountApp::CAccountApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_listTotalAccount.RemoveAll();
    m_listBankAccount.RemoveAll();
	m_listMoneyAccount.RemoveAll();
	m_nAccountType = 0;
	m_timeCur = COleDateTime::GetCurrentTime();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAccountApp object

CAccountApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAccountApp initialization

BOOL CAccountApp::InitInstance()
{
	AfxEnableControlContainer();
	
	CoInitialize(NULL);
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
 
	CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2003));

    //Connect the database
	CString strFile,strSource;
	char path[256];
	
	::GetModuleFileName(NULL,path,256);
	
	strFile=(CString)path;
	strFile=strFile.Left(strFile.ReverseFind('\\')+1)+"Account.mdb";
    strSource.Format("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;Jet OLEDB:Database Password=auqf_pgf_rd",strFile);

	m_db = new CADODatabase;
	BOOL bRet = m_db->Open(strSource);
	if(!bRet)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("错误"),MB_OK|MB_ICONWARNING);
		return FALSE;
	}
    Init();

	CAccountDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
    
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CAccountApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	// 注销COM库
	CoUninitialize();

	//delete the users
    for (int i=0;i<2;i++)
    {
		if(m_user[i])
		{
			delete m_user[i];
			m_user[i] = NULL;
		}
    }
	//delete the accounts
	for( i=0;i<m_listTotalAccount.GetSize();i++)
	{
		CAccount* pAccount = m_listTotalAccount.GetAt(i);
		delete pAccount;
		pAccount = NULL;
	}
	m_listTotalAccount.RemoveAll();
    m_listBankAccount.RemoveAll();
	m_listMoneyAccount.RemoveAll();

	if(m_db)
	{
		if(m_db->IsOpen())
			m_db->Close();
		delete m_db;
		m_db = NULL;
	}
	//
	BCGCBProCleanUp ();

	return CWinApp::ExitInstance();
}

void CAccountApp::Init()
{
	//Init the users
	CString strSql;
	CADORecordset rs(GetDB());
	if(rs.Open(_T("select * from Power order by PowerIndex asc"),CADORecordset::openQuery))
	{
		for(int i=0;i<2;i++)
		{
			m_user[i] = new CUser;
			m_user[i]->LoadInfo(rs);

			rs.MoveNext();
		}
		rs.Close();
	}
	//Init the account
	if(rs.Open(_T("select * from Account order by AccountIndex asc"),CADORecordset::openQuery))
	{
         while (!rs.IsEOF())
         {
			 CAccount* pAccount = new CAccount;
			 pAccount->LoadInfo(rs);
			 //Load the money
			 CADORecordset rs1(GetDB());
			 strSql.Format("select * from MoneyTable where MoneyAccount=%d order by MoneyCreateTime",pAccount->GetID());

			 if(rs1.Open(strSql,CADORecordset::openQuery))
			 {
				 while (!rs1.IsEOF())
				 {
					 CMoneyOper* pMoney = new CMoneyOper;
							 
					 pMoney->AddTo(pAccount);			 
					 pMoney->LoadInfo(rs1);                     

					 rs1.MoveNext();
				 }
				 rs1.Close();
			 }
			 SetAccount(pAccount);

			 rs.MoveNext();
		 }
		 rs.Close();
	}
}

CDataBase* CAccountApp::GetUser(int i/* =0 */)
{
	if( i >=0 && i<2 )
		return m_user[i];
	else
	    return NULL;
}

CArray<CAccount*,CAccount*>& CAccountApp::GetAccountList(int nType/* =0  */)
{
	if(nType == 0)
		return m_listTotalAccount;
	else if(nType ==1)
		return m_listBankAccount;
	else
		return m_listMoneyAccount;

}

void CAccountApp::SetAccount(CAccount* pAccount)
{
	ASSERT(pAccount!=NULL);

	m_listTotalAccount.Add(pAccount);
	
	if(pAccount->m_type == CAccount::ACCOUNT_BANK)
		m_listBankAccount.Add(pAccount);
	else
		m_listMoneyAccount.Add(pAccount);
}