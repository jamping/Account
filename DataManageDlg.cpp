// DataManageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Account.h"
#include "DataManageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataManageDlg dialog


CDataManageDlg::CDataManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataManageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataManageDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDataManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataManageDlg)
	DDX_Control(pDX, IDC_RESTORE, m_btnRestore);
	DDX_Control(pDX, IDC_BACKUP, m_btnBackup);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataManageDlg, CDialog)
	//{{AFX_MSG_MAP(CDataManageDlg)
	ON_BN_CLICKED(IDC_BACKUP, OnBackup)
	ON_BN_CLICKED(IDC_RESTORE, OnRestore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataManageDlg message handlers

BOOL CDataManageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_btnBackup.SetImage(IDB_BACKUP);
	m_btnBackup.SizeToContent();
	m_btnRestore.SetImage(IDB_LOAD);
	m_btnRestore.SizeToContent();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDataManageDlg::OnBackup() 
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

void CDataManageDlg::OnRestore() 
{
	// TODO: Add your control notification handler code here
	CFileDialog fileDlg(TRUE,"mdb","*.mdb",	OFN_FILEMUSTEXIST| OFN_HIDEREADONLY,"Microsoft Access 数据库(*.mdb)|*.mdb||");
	
	BOOL bRet = FALSE;
    CString strExePath = _T("");

	if(fileDlg.DoModal()==IDOK)
	{		
		CString strFile;
		char path[256];
		
		::GetModuleFileName(NULL,path,256);

		strFile=(CString)path;
		strExePath = strFile;
		strFile=strFile.Left(strFile.ReverseFind('\\')+1)+"Account.mdb";

		bRet = CopyFile(fileDlg.GetPathName(),strFile,FALSE);
	}
	MessageBox(bRet?_T("数据恢复成功!"):_T("数据恢复失败!"));

	if(bRet)
	{
		AfxGetMainWnd()->SendMessage(WM_CLOSE);
        
		ShellExecute(NULL,"open",strExePath,NULL, NULL, SW_SHOWNORMAL);
	}
}
