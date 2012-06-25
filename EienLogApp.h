// EienLog.h : main header file for the EIENLOG application
//

#if !defined(AFX_EIENLOG_H__07FC1351_AF84_47B9_9525_1E8E6906B58C__INCLUDED_)
#define AFX_EIENLOG_H__07FC1351_AF84_47B9_9525_1E8E6906B58C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#ifndef __AFXWIN_H__
	//#error include 'stdafx.h' before including this file for PCH
//#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEienLogApp:
// See EienLog.cpp for the implementation of this class
//

class CEienLogApp : public CWinApp
{
public:
	CEienLogApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEienLogApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEienLogApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EIENLOG_H__07FC1351_AF84_47B9_9525_1E8E6906B58C__INCLUDED_)
