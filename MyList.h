#if !defined(AFX_MYLIST_H__5B131227_C129_4B92_B2E1_802AC7F70A0E__INCLUDED_)
#define AFX_MYLIST_H__5B131227_C129_4B92_B2E1_802AC7F70A0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyList.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CMyList window
#ifdef _DEBUG
	#define ASSERT_VALID_STRING( str ) ASSERT( !IsBadStringPtr( str, 0xfffff ) )
#else	//	_DEBUG
	#define ASSERT_VALID_STRING( str ) ( (void)0 )
#endif	//	_DEBUG

class CMyList : public CBCGPListCtrl
{
	friend class CAccountLogDlg;
// Construction
public:
	CMyList();

// Attributes
public:

// Operations
public:
	BOOL SetHeadings( const CString& strHeadings );
	int AddItem( LPCTSTR pszText, ... );
	int AddItem( CStringArray& aryItemTexts);
	BOOL DeleteItem( int iItem );
	BOOL DeleteAllItems();
	BOOL SetItemText( int nItem, int nSubItem, LPCTSTR lpszText );
	COLORREF GetItemTextColor(int nItem, int nSubItem);
	BOOL SetItemTextColor( int nItem, int nSubItem, COLORREF color=RGB(255,0,0) );
	BOOL SetItemData(int nItem, DWORD dwData);
	DWORD GetItemData(int nItem) const;
    int GetColumnCount() { return m_iNumColumns; }
	CString GetColumnName(int nCol);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyList)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyList() {}

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyList)
	afx_msg void OnDestroy();
	//}}AFX_MSG
    virtual COLORREF OnGetCellTextColor (int nRow, int nColum);
    virtual int OnCompareItems (LPARAM lParam1, LPARAM lParam2, int iColumn);

	void FreeItemMemory( const int iItem );
	BOOL SetTextArray( int iItem, LPTSTR* arrpsz );
	LPTSTR* GetTextArray( int iItem ) const;

    int m_iNumColumns;

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLIST_H__5B131227_C129_4B92_B2E1_802AC7F70A0E__INCLUDED_)
