// ReportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Account.h"
#include "ReportDlg.h"
#include "MakeReportDlg.h"
#include "MoneyOper.h"
#include "MoneyDlg.h"
#include  <math.h>
#include <ole2.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportDlg dialog


CReportDlg::CReportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReportDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReportDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_listMoney.RemoveAll();
}


void CReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportDlg)
	DDX_Control(pDX, IDC_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_DEL, m_btnDel);
	DDX_Control(pDX, IDC_MAKE_REPORT, m_btnMakeReport);
	DDX_Control(pDX, IDC_MAKE_EXCEL, m_btnMakeExcel);
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportDlg, CDialog)
	//{{AFX_MSG_MAP(CReportDlg)
	ON_BN_CLICKED(IDC_MAKE_EXCEL, OnMakeExcel)
	ON_BN_CLICKED(IDC_MAKE_REPORT, OnMakeReport)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(IDC_MAKE_EXCEL,OnUpdateMakeExcel)
	ON_UPDATE_COMMAND_UI(IDC_EDIT,OnUpdateEdit)
	ON_UPDATE_COMMAND_UI(IDC_DEL,OnUpdateDel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportDlg message handlers

BOOL CReportDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_btnMakeExcel.SetImage(IDB_EXCEL);
	m_btnMakeReport.SetImage(IDB_MAKEREPORT);
	m_btnEdit.SetImage(IDB_EDIT);
    m_btnDel.SetImage(IDB_DELETE);
	
	m_list.SetHeadings(_T("记录号,60;单据编号,80;录入时间,90;账户名称,100;客户名称,80;收入,80;支出,80;合计,80;业务员,80;收支种类,80;类别,80;凭证, 80;备注,150;"));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReportDlg::OnMakeExcel() 
{
	// TODO: Add your control notification handler code here	
	// 获得EXCEL的CLSID
	CLSID clsid;
	HRESULT hr = CLSIDFromProgID(L"Excel.Application", &clsid);
	
	if(FAILED(hr)) {
		MessageBox( "CLSIDFromProgID() 函数调用失败！", "错误", 0x10010);
		return ;
	}
	
	// 创建实例
	IDispatch *pXlApp;
	hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void **)&pXlApp);
	if(FAILED(hr)) {
		MessageBox( "请检查是否已经安装EXCEL！", "错误", 0x10010);
		return ;
	}
	
	// 显示，将Application.Visible属性置1
	VARIANT x;
	x.vt = VT_I4;
	x.lVal = 1;
	AutoWrap(DISPATCH_PROPERTYPUT, NULL, pXlApp, L"Visible", 1, x);
	
	// 获取Workbooks集合
	IDispatch *pXlBooks;
	{
		VARIANT result;
		VariantInit(&result);
		AutoWrap(DISPATCH_PROPERTYGET, &result, pXlApp, L"Workbooks", 0);
		pXlBooks = result.pdispVal;
	}
	
	// 调用Workbooks.Add()方法，创建一个新的Workbook
	IDispatch *pXlBook;
	{
		VARIANT result;
		VariantInit(&result);
		AutoWrap(DISPATCH_PROPERTYGET, &result, pXlBooks, L"Add", 0);
		pXlBook = result.pdispVal;
	}
	
	// 创建一个数组，用于填充表格
	VARIANT arr;
	arr.vt = VT_ARRAY | VT_VARIANT;
	SAFEARRAYBOUND sab[2];
	//增加4行，用于填充报表日期、空行、表头和汇总数据
 	sab[0].lLbound = 1; sab[0].cElements = m_list.GetItemCount()+3;
 	sab[1].lLbound = 1; sab[1].cElements = m_list.GetColumnCount();
	
	arr.parray = SafeArrayCreate(VT_VARIANT, 2, sab);
	
	// 初始化数组内容
	// 填充日期
    VARIANT tmp;
    VariantInit(&tmp);
	tmp.vt = VT_BSTR;	
	tmp.bstrVal = COleDateTime::GetCurrentTime().Format("报表日期：%Y年%m月%d日").AllocSysString();
	long indices[] = {1,1};
	SafeArrayPutElement(arr.parray, indices, (void *)&tmp);
	// 装载表头
	for(int i=0;i<m_list.GetColumnCount();i++)
	{
		VariantInit(&tmp);
		tmp.vt = VT_BSTR;
		tmp.bstrVal = m_list.GetColumnName(i).AllocSysString();
		// 添加数据到数组中
		indices[0] = 3;
		indices[1] = i+1;
		SafeArrayPutElement(arr.parray, indices, (void *)&tmp);
	}
	// 装载数据
	for(i=1; i<=m_list.GetItemCount(); i++) 
	{
		for(int j=1; j<=m_list.GetColumnCount(); j++) 
		{
			VariantInit(&tmp);
			tmp.vt = VT_BSTR;
			tmp.bstrVal = m_list.GetItemText(i-1,j-1).AllocSysString();
			// 添加数据到数组中
			indices[0] = i+3;
		    indices[1] = j;
			SafeArrayPutElement(arr.parray, indices, (void *)&tmp);
		}
	}
// 	//汇总收支情况
// 	double dwIncome=0.0,dwOutcome=0.0,dwTotal=0.0;
//     for(i=0;i<m_list.GetItemCount();i++)
// 	{
// 		dwIncome += atof(m_list.GetItemText(i,5));
// 		dwOutcome += atof(m_list.GetItemText(i,6));
// 		dwTotal += atof(m_list.GetItemText(i,7));
// 	}
// 	VariantInit(&tmp);
// 	tmp.vt = VT_BSTR;
// 	tmp.bstrVal = SysAllocString(L"合计");
// 	indices[0] = m_list.GetItemCount()+4;
// 	indices[1] = 1;
// 	SafeArrayPutElement(arr.parray, indices, (void *)&tmp);
//     
// 	VariantInit(&tmp);
// 	tmp.vt = VT_R8;
// 	tmp.dblVal = dwIncome;
//     indices[1] = 6;
// 	SafeArrayPutElement(arr.parray, indices, (void *)&tmp);
// 
// 	VariantInit(&tmp);
// 	tmp.vt = VT_R8;
// 	tmp.dblVal = dwOutcome;
//     indices[1] = 7;
// 	SafeArrayPutElement(arr.parray, indices, (void *)&tmp);
// 
// 	VariantInit(&tmp);
// 	tmp.vt = VT_R8;
// 	tmp.dblVal = dwTotal;
//     indices[1] = 8;
// 	SafeArrayPutElement(arr.parray, indices, (void *)&tmp);
	// 从Application.ActiveSheet属性获得Worksheet对象
	IDispatch *pXlSheet;
	{
		VARIANT result;
		VariantInit(&result);
		AutoWrap(DISPATCH_PROPERTYGET, &result, pXlApp, L"ActiveSheet", 0);
		pXlSheet = result.pdispVal;
	}
	
	// 选择一个Range
	IDispatch *pXlRange;
	{
		VARIANT parm;
		WCHAR szTmp[32];
        char c ='A'+m_list.GetColumnCount()-1;

		parm.vt = VT_BSTR;
		wsprintfW(szTmp,L"A1:%c%i",c,m_list.GetItemCount()+3);
		parm.bstrVal = ::SysAllocString(szTmp);

		VARIANT result;
		VariantInit(&result);
		AutoWrap(DISPATCH_PROPERTYGET, &result, pXlSheet, L"Range", 1, parm);
		VariantClear(&parm);
		
		pXlRange = result.pdispVal;
	}
	
	// 用我们的数组填充这个Range
	AutoWrap(DISPATCH_PROPERTYPUT, NULL, pXlRange, L"Value", 1, arr);
	
	// 退出，调用Application.Quit()方法
//	AutoWrap(DISPATCH_METHOD, NULL, pXlApp, L"Quit", 0);
	
	// 释放所有的接口以及变量
	pXlRange->Release();
	pXlSheet->Release();
	pXlBook->Release();
	pXlBooks->Release();
	pXlApp->Release();
	VariantClear(&arr);	

}
// AutoWrap() - Automation helper function...
HRESULT CReportDlg::AutoWrap(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, int cArgs...) {
    // Begin variable-argument list...
    va_list marker;
    va_start(marker, cArgs);
  
	ASSERT(pDisp!=NULL);

    // Variables used...
    DISPPARAMS dp = { NULL, NULL, 0, 0 };
    DISPID dispidNamed = DISPID_PROPERTYPUT;
    DISPID dispID;
    HRESULT hr;
    char buf[200];
    char szName[200];
	
    // Convert down to ANSI
    WideCharToMultiByte(CP_ACP, 0, ptName, -1, szName, 256, NULL, NULL);
	
    // Get DISPID for name passed...
    hr = pDisp->GetIDsOfNames(IID_NULL, &ptName, 1, LOCALE_USER_DEFAULT, &dispID);
    if(FAILED(hr)) {
        sprintf(buf, "IDispatch::GetIDsOfNames(\"%s\") failed w/err 0x%08lx", szName, hr);
        ::MessageBox(NULL, buf, "AutoWrap()", 0x10010);
        return hr;
    }
	
    // Allocate memory for arguments...
    VARIANT *pArgs = new VARIANT[cArgs+1];
    // Extract arguments...
    for(int i=0; i<cArgs; i++) {
        pArgs[i] = va_arg(marker, VARIANT);
    }
	
    // Build DISPPARAMS
    dp.cArgs = cArgs;
    dp.rgvarg = pArgs;
	
    // Handle special-case for property-puts!
    if(autoType & DISPATCH_PROPERTYPUT) {
        dp.cNamedArgs = 1;
        dp.rgdispidNamedArgs = &dispidNamed;
    }
	
    // Make the call!
    hr = pDisp->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, autoType, &dp, pvResult, NULL, NULL);
    if(FAILED(hr)) {
        sprintf(buf, "IDispatch::Invoke(\"%s\"=%08lx) failed w/err 0x%08lx", szName, dispID, hr);
        ::MessageBox(NULL, buf, "AutoWrap()", 0x10010);
    }
    // End variable-argument section...
    va_end(marker);
	
    delete [] pArgs;
	
    return hr;
}
void CReportDlg::OnMakeReport() 
{
	// TODO: Add your control notification handler code here
	CMakeReportDlg dlg;

	if(dlg.DoModal() == IDOK)
	{   
		m_listMoney.RemoveAll();
		
		for(int i=0;i<dlg.m_listSelAccount.GetSize();i++)
		{
			CAccount* pAccount = dlg.m_listSelAccount.GetAt(i);
			for(int j=0;j<pAccount->m_childMoney.GetSize();j++)
			{
				 m_listMoney.Add(pAccount->m_childMoney.GetAt(j));
			}
		}
		if(dlg.m_nType != 0)
		{
			for(i=0;i<m_listMoney.GetSize();i++)
			{
				if(dlg.m_nType == 1)
				{
					 if(m_listMoney.GetAt(i)->m_dwMoneySum<0)
					 {
						 m_listMoney.RemoveAt(i--);
					 }
				}
				else
				{
					if(m_listMoney.GetAt(i)->m_dwMoneySum>0)
					{
						m_listMoney.RemoveAt(i--);
					}
				}
			}
		}
		if(dlg.m_bTime)
		{
			for( i=0;i<m_listMoney.GetSize();i++)
			{
				if(m_listMoney.GetAt(i)->m_timeCreate<dlg.m_time1 || m_listMoney.GetAt(i)->m_timeCreate>dlg.m_time2)
					m_listMoney.RemoveAt(i--);
			}
		}
        if(dlg.m_bMoney)
		{
			for( i=0;i<m_listMoney.GetSize();i++)
			{
				if(fabs(m_listMoney.GetAt(i)->m_dwMoneySum)<dlg.m_dwMoney1 || fabs(m_listMoney.GetAt(i)->m_dwMoneySum)>dlg.m_dwMoney1)
					m_listMoney.RemoveAt(i--);
			}
		}
		if(!dlg.m_strNumber.IsEmpty())
		{
			for(i=0;i<m_listMoney.GetSize();i++)
			{
				if(dlg.m_strNumber.CompareNoCase(m_listMoney.GetAt(i)->m_strMoneySerial)!=0)
					m_listMoney.RemoveAt(i--);
			}
		}
		if(!dlg.m_strCustomer.IsEmpty() && dlg.m_strCustomer.Compare(_T("所有"))!=0)
		{
			for(i=0;i<m_listMoney.GetSize();i++)
			{
				if(dlg.m_strCustomer.CompareNoCase(m_listMoney.GetAt(i)->m_strMoneyUser)!=0)
					m_listMoney.RemoveAt(i--);
			}
		}
		if(!dlg.m_strIncomeType.IsEmpty()&& dlg.m_strIncomeType.Compare(_T("所有"))!=0)
		{
			for(i=0;i<m_listMoney.GetSize();i++)
			{
				if(dlg.m_strIncomeType.CompareNoCase(m_listMoney.GetAt(i)->m_strMoneyReason)!=0)
					m_listMoney.RemoveAt(i--);
			}
		}
		if(!dlg.m_strPayType.IsEmpty()&& dlg.m_strPayType.Compare(_T("所有"))!=0)
		{
			for(i=0;i<m_listMoney.GetSize();i++)
			{
				if(dlg.m_strPayType.CompareNoCase(m_listMoney.GetAt(i)->m_strMoneyType)!=0)
					m_listMoney.RemoveAt(i--);
			}
		}
		if(!dlg.m_strPayItemType.IsEmpty()&& dlg.m_strPayItemType.Compare(_T("所有"))!=0)
		{
			for(i=0;i<m_listMoney.GetSize();i++)
			{
				if(dlg.m_strPayItemType.CompareNoCase(m_listMoney.GetAt(i)->m_strMoneyToken)!=0)
					m_listMoney.RemoveAt(i--);
			}
		}
		if(!dlg.m_strRemark.IsEmpty())
		{
			for(i=0;i<m_listMoney.GetSize();i++)
			{
				if(dlg.m_strRemark.CompareNoCase(m_listMoney.GetAt(i)->m_strMoneyRemark)!=0)
					m_listMoney.RemoveAt(i--);
			}
		}
		ShowMoneyOper();
	}
}
void CReportDlg::ShowMoneyOper()
{
	m_list.DeleteAllItems();
 
	double dwIncome = 0.0;
	double dwOutcome = 0.0;
    double dwTotal = 0.0;

	for(int i=0;i<m_listMoney.GetSize();i++)
	{
		CString str;
		CStringArray strList;
		
		CMoneyOper* pMoney = m_listMoney.GetAt(i);

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
		
		dwIncome += pMoney->m_dwMoneyIn;
		dwOutcome += pMoney->m_dwMoneyOut;
		dwTotal += pMoney->m_dwMoneySum;

		if(pMoney->m_dwMoneySum < 0.0)
		{
			m_list.SetItemTextColor(nIndex,7);
		}
	}
	//插入统计数据
	 CString  strIncome,strOutcome,strTotal;
	 strIncome.Format("%0.2f",dwIncome);
	 strOutcome.Format("%0.2f",dwOutcome);
	 strTotal.Format("%0.2f",dwTotal);

     int nIndex = m_list.AddItem(_T("合计"),_T(""),_T(""),_T(""),_T(""),strIncome,strOutcome,strTotal,_T(""),_T(""),_T(""),_T(""),_T(""));
	 m_list.SetItemTextColor(nIndex,5);
	 m_list.SetItemTextColor(nIndex,6);
	 m_list.SetItemTextColor(nIndex,7);
}
void CReportDlg::EditListItem(CMyList& listCtrl,int nItem)
{
	CMoneyOper* pMoney=(CMoneyOper*)listCtrl.GetItemData(nItem);
	if(pMoney == NULL)
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
		ShowMoneyOper();
		
		MessageBox(_T("记录修改成功！"));
	}
}

void CReportDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
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

void CReportDlg::OnDel() 
{
	// TODO: Add your control notification handler code here
	if(MessageBox(_T("确实要删除选择的记录吗？"),_T("请确认"),MB_YESNO|MB_ICONQUESTION) == IDNO)
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
			 //Delete from the list first
			 for(int j=0;j<m_listMoney.GetSize();j++)
			 {
				 if(pMoney->GetID() == m_listMoney.GetAt(j)->GetID())
				 {
					 m_listMoney.RemoveAt(j);
					 break;
				 }
			 }
             //Delete Money from the Account
			 CAccount* pAccount = pMoney->m_pAccount;
			 pAccount->DeleteMoney(pMoney);
		}
	}
	AfxGetMainWnd()->SendMessage(WM_UPDATE_INFO);
	ShowMoneyOper();
}

BOOL CReportDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateDialogControls(this,FALSE);
	return CDialog::PreTranslateMessage(pMsg);
}
void CReportDlg::OnUpdateMakeExcel(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_list.GetItemCount() > 0);
}
void CReportDlg::OnUpdateDel(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_list.GetSelectedCount() > 0);
}
void CReportDlg::OnUpdateEdit(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_list.GetSelectedCount() == 1);
}
void CReportDlg::OnEdit() 
{
	// TODO: Add your control notification handler code here
	UINT uSelectedCount = m_list.GetSelectedCount();
	ASSERT(uSelectedCount == 1);
	
	int  nItem = -1;
	nItem = m_list.GetNextItem(nItem, LVNI_SELECTED);
	ASSERT(nItem != -1);
	EditListItem(m_list,nItem);
}
