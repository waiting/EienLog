/**************************************************************************
 图片框
 显示图片用,可new,设置AutoDelete为真可自动删除
 **************************************************************************/
#if !defined(AFX_IMAGEBOX_H__91D80D2C_9210_4663_A471_13F634744813__INCLUDED_)
#define AFX_IMAGEBOX_H__91D80D2C_9210_4663_A471_13F634744813__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageBox.h : header file
//

#include "Window.h"
/////////////////////////////////////////////////////////////////////////////
// ImageBox window
class ImageBox : public Window
{
// Construction
public:
	enum ImageBoxNotify
	{
		ibnClick,
		ibnDblClk,
		ibnContextMenu,
	};
	enum
	{
		IBM_NOTIFY = WM_USER + 1001
	};

	ImageBox( BOOL bAutoDel );
	virtual ~ImageBox();

	BOOL Create( DWORD dwStyle, RECT const & rect, CWnd * pParentWnd, UINT nID );
public:
	// Attributes
	CString GetImagePath() const { return _strImagePath; }
	COLORREF GetColor() const { return _clrColor; }
	// Operations
	void DisplayImage( LPCTSTR lpszPath );
	void DisplayColor( COLORREF color );
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ImageBox)

	//}}AFX_VIRTUAL
protected:
	void DisplayImage( Image * pImage );
	CString _strImagePath;
	COLORREF _clrColor;
	BOOL _bLeftButtonDown;
	MemImage _CacheImg;
protected:
	// Generated message map functions
	//{{AFX_MSG(ImageBox)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu( CWnd * pWnd, CPoint point );
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEBOX_H__91D80D2C_9210_4663_A471_13F634744813__INCLUDED_)
