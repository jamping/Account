// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__2E05FD74_3E9B_4B93_81FD_519DACDDF71A__INCLUDED_)
#define AFX_STDAFX_H__2E05FD74_3E9B_4B93_81FD_519DACDDF71A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <BCGCBProInc.h>			// BCGPro Control Bar
#include "ado.h"
#include "Des.h"

#define  WM_UPDATE_INFO WM_USER+100

#pragma warning(disable : 4018)
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__2E05FD74_3E9B_4B93_81FD_519DACDDF71A__INCLUDED_)
