#if !defined(AFX_WINDOW_H__E8E25A6B_5104_4140_89A1_D7F7DC3CA079__INCLUDED_)
#define AFX_WINDOW_H__E8E25A6B_5104_4140_89A1_D7F7DC3CA079__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Window.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Window window

class Window : public CWnd
{
// Construction
public:
	Window();
	virtual ~Window();

// Attributes
public:
	void AutoDelete( BOOL bAutoDel ) { _bAutoDelete = bAutoDel; } // 自动删除对象,当new分配时又不想管理内存,请设置其为TRUE
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Window)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation

	// Generated message map functions
protected:
	BOOL _bAutoDelete;
	//{{AFX_MSG(Window)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINDOW_H__E8E25A6B_5104_4140_89A1_D7F7DC3CA079__INCLUDED_)
