// AccountLogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Account.h"
#include "AccountLogDlg.h"
#include "MoneyOper.h"
#include "MoneyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAccountLogDlg dialog


CAccountLogDlg::CAccountLogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAccountLogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAccountLogDlg)
	m_strLastDayLeft = _T("");
	m_strTodayIncome = _T("");
	m_strTodayLeft = _T("");
	m_strTodayOutcome = _T("");
	//}}AFX_DATA_INIT
}


void CAccountLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAccountLogDlg)
	DDX_Control(pDX, IDC_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_DEL, m_btnDel);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_LASTDAY_LEFT, m_strLastDayLeft);
	DDX_Text(pDX, IDC_TODAY_INCOME, m_strTodayIncome);
	DDX_Text(pDX, IDC_TODAY_LEFT, m_strTodayLeft);
	DDX_Text(pDX, IDC_TODAY_OUTCOME, m_strTodayOutcome);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAccountLogDlg, CDialog)
	//{{AFX_MSG_MAP(CAccountLogDlg)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(IDC_EDIT,OnUpdateEdit)
	ON_UPDATE_COMMAND_UI(IDC_DEL,OnUpdateDel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAccountLogDlg message handlers

BOOL CAccountLogDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_btnEdit.SetImage(IDB_EDIT);
	m_btnDel.SetImage(IDB_DELETE);
	
	m_list.SetHeadings(_T("��¼��,60;���ݱ��,80;¼��ʱ��,90;�˻�����,100;�ͻ�����,80;����,80;֧��,80;�ϼ�,80;ҵ��Ա,80;��֧����,80;���,80;ƾ֤, 80;��ע,150;"));
	
	ShowMoneyOper(theApp.m_timeCur,theApp.GetAccountType());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CAccountLogDlg::ShowMoneyOper(COleDateTime timeCur,int nAccountType /* =0 */)
{
	 m_list.DeleteAllItems();
     
	 double dwTodayTotal = 0.0;
	 UINT   nTodayIncome = 0;
	 UINT   nTodayOutcome = 0;
     double dwTodayIncome = 0.0;
	 double dwTodayOutcome = 0.0;

	 for(int i=0;i<theApp.GetAccountList(nAccountType).GetSize();i++)
	 {
		 CAccount* pAccount = theApp.GetAccountList(nAccountType).GetAt(i);
		 pAccount->ComputerMoney(timeCur);
		 dwTodayTotal += pAccount->m_dwAccountLeft;

		 for(int j=0;j<pAccount->m_childMoney.GetSize();j++)
		 {
			 CMoneyOper* pMoney = pAccount->m_childMoney.GetAt(j);
			 if(  pMoney->m_timeCreate.GetYear() == timeCur.GetYear() 
				&& pMoney->m_timeCreate.GetMonth() == timeCur.GetMonth()
				&& pMoney->m_timeCreate.GetDay() == timeCur.GetDay() )
			 {
				  CString str;
                  CStringArray strList;

				  str.Format("%d",pMoney->GetID());
				  strList.Add(str);

				  strList.Add(pMoney->m_strMoneySerial);
				  strList.Add(pMoney->m_timeCreate.Format("%Y-%m-%d"));
				  strList.Add(pMoney->m_pAccount->GetDesc());
				  strList.Add(pMoney->m_strMoneyUser);
				  str.Format("%0.2f",pMoney->m_dwMoneyIn);
				  strList.Add(str);
				  str.Format("%0.2f",pMoney->m_dwMoneyOut);
				  strList.Add(str);
				  str.Format("%0.2f",pMoney->m_dwMoneySum);
				  strList.Add(str);
				  strList.Add(pMoney->m_strMoneyMan);
				  strList.Add(pMoney->m_strMoneyReason);
				  strList.Add(pMoney->m_strMoneyType);
				  strList.Add(pMoney->m_strMoneyToken);
				  strList.Add(pMoney->m_strMoneyRemark);

				  int nIndex = m_list.AddItem(strList);
				  m_list.SetItemData(nIndex,(DWORD)pMoney);	

                  if(pMoney->m_dwMoneySum < 0.0)
				  {
					  m_list.SetItemTextColor(nIndex,7);
					  nTodayOutcome++;
					  dwTodayOutcome += pMoney->m_dwMoneyOut;
				  }
				  else
				  {
					  nTodayIncome++;
					  dwTodayIncome += pMoney->m_dwMoneyIn;
				  }				  
			 }
		 }
	 }
	 m_strLastDayLeft.Format("���ս��ࣺ%0.2fԪ",dwTodayTotal-(dwTodayIncome-dwTodayOutcome));
	 m_strTodayLeft.Format("���ս��ࣺ%0.2fԪ",dwTodayTotal);
	 m_strTodayIncome.Format("�������룺��%d�ʡ�%0.2fԪ",nTodayIncome,dwTodayIncome);
	 m_strTodayOutcome.Format("����֧������%d�ʡ�%0.2fԪ",nTodayOutcome,dwTodayOutcome);
     //����ͳ������
	 CString  strIncome,strOutcome,strTotal;
	 strIncome.Format("%0.2f",dwTodayIncome);
	 strOutcome.Format("%0.2f",dwTodayOutcome);
	 strTotal.Format("%0.2f",dwTodayIncome-dwTodayOutcome);

     int nIndex = m_list.AddItem(_T("�ϼ�"),_T(""),_T(""),_T(""),_T(""),strIncome,strOutcome,strTotal,_T(""),_T(""),_T(""),_T(""),_T(""));
	 m_list.SetItemTextColor(nIndex,5);
	 m_list.SetItemTextColor(nIndex,6);
	 m_list.SetItemTextColor(nIndex,7);

	 UpdateData(FALSE);
}

void CAccountLogDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	 NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	 int nItem=pNMListView->iItem;

	 if(nItem!=-1)
	 {
		 EditListItem(m_list,nItem);
	 }

	*pResult = 0;
}

void CAccountLogDlg::OnDel() 
{
	// TODO: Add your control notification handler code here
	if(MessageBox(_T("ȷʵҪɾ��ѡ��ļ�¼��"),_T("��ȷ��"),MB_YESNO|MB_ICONQUESTION) == IDNO)
		return;

	UINT i, uSelectedCount = m_list.GetSelectedCount();
	ASSERT(uSelectedCount>0);
	
	// Delete all of the selected items.
	int  nItem = -1;	
	for (i=0;i < uSelectedCount;i++)
	{
		nItem = m_list.GetNextItem(nItem, LVNI_SELECTED);
		ASSERT(nItem != -1);
       //Delete the nItem
        CMoneyOper* pMoney=(CMoneyOper*)m_list.GetItemData(nItem);
		if(pMoney == NULL)
			continue;
        //Delete the data from database
        if(pMoney->DeleteFromDB(theApp.GetDB()))
		{
             //Delete Money from the Account
			 CAccount* pAccount = pMoney->m_pAccount;
			 pAccount->DeleteMoney(pMoney);
		}
	}
	AfxGetMainWnd()->SendMessage(WM_UPDATE_INFO);
}

void CAccountLogDlg::OnEdit() 
{
	// TODO: Add your control notification handler code here
	UINT uSelectedCount = m_list.GetSelectedCount();
	ASSERT(uSelectedCount == 1);
	
	int  nItem = -1;
	nItem = m_list.GetNextItem(nItem, LVNI_SELECTED);
	ASSERT(nItem != -1);
	EditListItem(m_list,nItem);
}

BOOL CAccountLogDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateDialogControls(this,FALSE);

	return CDialog::PreTranslateMessage(pMsg);
}
void CAccountLogDlg::OnUpdateEdit(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_list.GetSelectedCount() == 1);
}
void CAccountLogDlg::OnUpdateDel(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_list.GetSelectedCount() > 0);
}
void CAccountLogDlg::EditListItem(CMyList& listCtrl,int nItem)
{
	CMoneyOper* pMoney=(CMoneyOper*)listCtrl.GetItemData(nItem);
	if(pMoney ==NULL)
		return;
	
	CMoneyDlg::MoneyDlgType type = CMoneyDlg::EDIT_GET;
	if(pMoney->m_dwMoneySum<0)
		type = CMoneyDlg::EDIT_PAY;
	
	CMoneyDlg dlg(type);
	dlg.SetValue(pMoney);
	if(dlg.DoModal()==IDOK)
	{
		dlg.GetValue(pMoney);
		
		pMoney->SaveToDB(theApp.GetDB());
		//Refresh the data
		AfxGetMainWnd()->SendMessage(WM_UPDATE_INFO);
		
		MessageBox(_T("��¼�޸ĳɹ���"));
	}
}
