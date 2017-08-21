// MyList.cpp : implementation file
//

#include "stdafx.h"
#include "Account.h"
#include "MyList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct ItemData
{
public:
  ItemData() : arrpsz( NULL ), dwData( NULL ),pTextColor(NULL) {}
  
  LPTSTR*   arrpsz;
  DWORD     dwData;
  COLORREF* pTextColor;
private:
  // ban copying.
  ItemData( const ItemData& );
  ItemData& operator=( const ItemData& );
};
/////////////////////////////////////////////////////////////////////////////
// CMyList

CMyList::CMyList():m_iNumColumns(0)
{
}

BEGIN_MESSAGE_MAP(CMyList, CBCGPListCtrl)
	//{{AFX_MSG_MAP(CMyList)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyList message handlers

void CMyList::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0,LVS_REPORT | LVS_EDITLABELS);
	SetExtendedStyle(GetExtendedStyle()|LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CBCGPListCtrl::PreSubclassWindow();
}
COLORREF CMyList::OnGetCellTextColor (int nRow, int nColumn)
{
    COLORREF color = GetItemTextColor(nRow,nColumn);
	if(color != -1)
		return color;

	return CBCGPListCtrl::OnGetCellTextColor (nRow, nColumn);
}


// the heading text is in the format column 1 text,column 1 width;column 2 text,column 3 width;etc.
BOOL CMyList::SetHeadings( const CString& strHeadings )
{
  int iStart = 0;
  
  for( ;; )
  {
    const int iComma = strHeadings.Find( _T(','), iStart );
    
    if( iComma == -1 )
      break;
    
    const CString strHeading = strHeadings.Mid( iStart, iComma - iStart );
    
    iStart = iComma + 1;
    
    int iSemiColon = strHeadings.Find( _T(';'), iStart );
    
    if( iSemiColon == -1 )
      iSemiColon = strHeadings.GetLength();
    
    const int iWidth = atoi( strHeadings.Mid( iStart, iSemiColon - iStart ) );
    
    iStart = iSemiColon + 1;
    
    if( InsertColumn( m_iNumColumns++, strHeading, LVCFMT_CENTER, iWidth ) == -1 )
      return FALSE;
  }
  
  return TRUE;
}
int CMyList::AddItem( LPCTSTR pszText, ... )
{
	const int iIndex = InsertItem( GetItemCount(), pszText );
	
	LPTSTR* arrpsz = new LPTSTR[ m_iNumColumns ];
	arrpsz[ 0 ] = new TCHAR[ lstrlen( pszText ) + 1 ];
	(void)lstrcpy( arrpsz[ 0 ], pszText );
	
	va_list list;
	va_start( list, pszText );
	
	for( int iColumn = 1; iColumn < m_iNumColumns; iColumn++ )
	{
		pszText = va_arg( list, LPCTSTR );
		ASSERT_VALID_STRING( pszText );
		VERIFY( CListCtrl::SetItem( iIndex, iColumn, LVIF_TEXT, pszText, 0, 0, 0, 0 ) );
		
		arrpsz[ iColumn ] = new TCHAR[ lstrlen( pszText ) + 1 ];
		(void)lstrcpy( arrpsz[ iColumn ], pszText );
	}
	
	va_end( list );
	
	VERIFY( SetTextArray( iIndex, arrpsz ) );
	
	return iIndex;
}
int CMyList::AddItem(CStringArray& aryItemTexts)
{
	const int iIndex = InsertItem( GetItemCount(), aryItemTexts.GetAt(0));
	
	LPTSTR* arrpsz = new LPTSTR[ m_iNumColumns ];
	for(int i =0;i<aryItemTexts.GetSize();i++)
	{
		arrpsz[ i ] = new TCHAR[ lstrlen( aryItemTexts.GetAt(i) ) + 1 ];
		(void)lstrcpy( arrpsz[ i ], aryItemTexts.GetAt(i) );
	}
	
	for( int iColumn = 1; iColumn < m_iNumColumns; iColumn++ )
	{
		VERIFY( CBCGPListCtrl::SetItem( iIndex, iColumn, LVIF_TEXT, arrpsz[iColumn], 0, 0, 0, 0 ) );
	}
	
	VERIFY( SetTextArray( iIndex, arrpsz ) );
	
	return iIndex;
}
void CMyList::FreeItemMemory( const int iItem )
{
	ItemData* pid = reinterpret_cast<ItemData*>( CBCGPListCtrl::GetItemData( iItem ) );
	
	LPTSTR* arrpsz = pid->arrpsz;
	
	for( int i = 0; i < m_iNumColumns; i++ )
		delete[] arrpsz[ i ];
	
	delete[] arrpsz;
	delete[] pid->pTextColor;
	delete pid;  
	
	VERIFY( CBCGPListCtrl::SetItemData( iItem, NULL ) );
}


BOOL CMyList::DeleteItem( int iItem )
{
	FreeItemMemory( iItem );
	return CBCGPListCtrl::DeleteItem( iItem );
}


BOOL CMyList::DeleteAllItems()
{
	for( int iItem = 0; iItem < GetItemCount(); iItem ++ )
		FreeItemMemory( iItem );  
	
	return CBCGPListCtrl::DeleteAllItems();
}

BOOL CMyList::SetItemText( int nItem, int nSubItem, LPCTSTR lpszText )
{
	if( !CBCGPListCtrl::SetItemText( nItem, nSubItem, lpszText ) )
		return FALSE;
	
	LPTSTR* arrpsz = GetTextArray( nItem );
	LPTSTR pszText = arrpsz[ nSubItem ];
	delete[] pszText;
	pszText = new TCHAR[ lstrlen( lpszText ) + 1 ];
	(void)lstrcpy( pszText, lpszText );
	arrpsz[ nSubItem ] = pszText;
	
	return TRUE;
}
BOOL CMyList::SetItemTextColor(int nItem, int nSubItem, COLORREF color/* =RGB */)
{
	if( nItem >= GetItemCount() )
		return FALSE;
	
	ItemData* pid = reinterpret_cast<ItemData*>( CBCGPListCtrl::GetItemData( nItem ) );
	ASSERT( pid );
	pid->pTextColor[nSubItem] = color;
	
	return TRUE;
}
COLORREF CMyList::GetItemTextColor(int nItem, int nSubItem)
{
    ASSERT( nItem < GetItemCount() );
	
	ItemData* pid = reinterpret_cast<ItemData*>( CBCGPListCtrl::GetItemData( nItem ) );
	ASSERT( pid );	
	
	return pid->pTextColor[nSubItem];
}
BOOL CMyList::SetItemData( int nItem, DWORD dwData )
{
	if( nItem >= GetItemCount() )
		return FALSE;
	
	ItemData* pid = reinterpret_cast<ItemData*>( CBCGPListCtrl::GetItemData( nItem ) );
	ASSERT( pid );
	pid->dwData = dwData;
	
	return TRUE;
}


DWORD CMyList::GetItemData( int nItem ) const
{
	ASSERT( nItem < GetItemCount() );
	
	ItemData* pid = reinterpret_cast<ItemData*>( CBCGPListCtrl::GetItemData( nItem ) );
	ASSERT( pid );
	return pid->dwData;
}


BOOL CMyList::SetTextArray( int iItem, LPTSTR* arrpsz )
{
	ASSERT( CBCGPListCtrl::GetItemData( iItem ) == NULL );
	ItemData* pid = new ItemData;
	pid->arrpsz = arrpsz;
	pid->pTextColor = new COLORREF [m_iNumColumns];
	for(int i=0;i<m_iNumColumns;i++)
		pid->pTextColor[i] = -1;
	
	return CBCGPListCtrl::SetItemData( iItem, reinterpret_cast<DWORD>( pid ) );
}


LPTSTR* CMyList::GetTextArray( int iItem ) const
{
	ASSERT( iItem < GetItemCount() );
	
	ItemData* pid = reinterpret_cast<ItemData*>( CListCtrl::GetItemData( iItem ) );
	return pid->arrpsz;
}

BOOL IsNumber( LPCTSTR pszText )
{
	ASSERT_VALID_STRING(pszText);
	int iDotCount=0;
	for(int i=0;i<lstrlen(pszText);i++){
		if(!_istdigit(pszText[i])){
			if(pszText[i] == '-' )
				continue;
			if(pszText[i]!='.')
				return FALSE;
			iDotCount++;
			if(iDotCount>1)
				return FALSE;
		}
	}
	return TRUE;
}

int NumberCompare( LPCTSTR pszNumber1, LPCTSTR pszNumber2 )
{
	ASSERT_VALID_STRING(pszNumber1);
	ASSERT_VALID_STRING(pszNumber2);
	
	const double fNumber1=atof(pszNumber1);
	const double fNumber2=atof(pszNumber2);
	
	if(fNumber1<fNumber2)
		return -1;
	else if(fNumber1>fNumber2)
		return 1;
	return 0;
}

BOOL IsDate( LPCTSTR pszText )
{
	ASSERT_VALID_STRING( pszText );
	
	COleDateTime time;
	
	return time.ParseDateTime(pszText);

	// format should be 9999-99-99 00:00:00.
	
// 	if( lstrlen( pszText ) < 10 && lstrlen( pszText)>19)
// 		return false;
// 	
// 	return _istdigit(pszText[0])
// 		&& _istdigit(pszText[1])    
// 		&& _istdigit( pszText[ 2 ] )
// 		&& _istdigit( pszText[ 3 ] )
// 		&& pszText[4]==_T('-')
// 		&& _istdigit( pszText[ 5 ] )
// 		&& _istdigit( pszText[ 6 ] )
// 		&& pszText[7]==_T('-')
// 		&& _istdigit( pszText[ 8 ] )
// 		&& _istdigit( pszText[ 9 ] );
}


int DateCompare( const CString& strDate1, const CString& strDate2 )
{
	COleDateTime time1,time2;
	if(!time1.ParseDateTime(strDate1))
        return -1;
	if(!time2.ParseDateTime(strDate2))
		return -1;
	
	if(time1<time2)
		return -1;
	else if(time1>time2)
		return 1;
	
	return 0;
}

void CMyList::OnDestroy() 
{
	for( int iItem = 0; iItem < GetItemCount(); iItem ++ )
        FreeItemMemory( iItem );

	CBCGPListCtrl::OnDestroy();	
	// TODO: Add your message handler code here
	
}
int CMyList::OnCompareItems (LPARAM lParam1, LPARAM lParam2, int iColumn)
{
    ItemData* pid1 = reinterpret_cast<ItemData*>( lParam1 );
	ItemData* pid2 = reinterpret_cast<ItemData*>( lParam2 );
	
	ASSERT( pid1 );
	ASSERT( pid2 );
	LPCTSTR pszText1 = pid1->arrpsz[ iColumn ];
	LPCTSTR pszText2 = pid2->arrpsz[ iColumn ];
	
	ASSERT_VALID_STRING( pszText1 );
	ASSERT_VALID_STRING( pszText2 );
	
	if(IsNumber(pszText1))
		return NumberCompare( pszText1, pszText2 );
	else if(IsDate(pszText1))
		return DateCompare( pszText1, pszText2 ) ;
	else
		// text.
		return lstrcmp( pszText1, pszText2 );
}
CString CMyList::GetColumnName(int nCol)
{
	CString str = _T("");
	TCHAR  buf [256];

	LVCOLUMN col;
    col.mask = LVCF_TEXT;
    col.pszText =buf;
	col.cchTextMax = 256;

	if(GetColumn(nCol,&col))
		str = col.pszText;

	return str;
}
