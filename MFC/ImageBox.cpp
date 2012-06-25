/*************************************
 ImageBox.cpp
 Í¼Æ¬¿ò
**************************************/

#include "ImageMerge.h"
#include "ImageBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ImageBox

ImageBox::ImageBox( BOOL bAutoDel )
{
	_strImagePath = "";
	_clrColor = 0;
	_bAutoDelete = bAutoDel;
	_bLeftButtonDown = FALSE;
}

ImageBox::~ImageBox()
{
}

BOOL ImageBox::Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID )
{
	return Window::Create( NULL, NULL, dwStyle, rect, pParentWnd, nID, NULL);	
}

BEGIN_MESSAGE_MAP(ImageBox, Window)
	//{{AFX_MSG_MAP(ImageBox)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CONTEXTMENU()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void ImageBox::DisplayImage( LPCTSTR lpszPath )
{
	_strImagePath = lpszPath;
	DisplayImage( &Image( StringToUnicode(lpszPath).c_str() ) );
}

void ImageBox::DisplayImage( Image * pImage )
{
	CRect rc;
	GetClientRect(&rc);
	_CacheImg.Create( rc.Width(), rc.Height() );
	Graphics g(_CacheImg);
	g.DrawImage( pImage, Rect( 0, 0, _CacheImg.Width(), _CacheImg.Height() ), 0, 0, pImage->GetWidth(), pImage->GetHeight(), UnitPixel );
	g.DrawRectangle( &Pen( COLORREFtoColor(0x000000) ), 0, 0, rc.Width() - 1, rc.Height() - 1 );
	Invalidate(TRUE);
}

void ImageBox::DisplayColor( COLORREF color )
{
	_clrColor = color;
	CRect rc;
	GetClientRect(&rc);
	_CacheImg.Create( rc.Width(), rc.Height() );

	Graphics g(_CacheImg);
	g.FillRectangle( &SolidBrush( COLORREFtoColor(color) ), 0, 0, rc.Width(), rc.Height() );
	g.DrawRectangle( &Pen( COLORREFtoColor(0x000000) ), 0, 0, rc.Width() - 1, rc.Height() - 1 );

	Invalidate(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// ImageBox message handlers

void ImageBox::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	int nID = GetDlgCtrlID();
	GetParent()->SendMessage( IBM_NOTIFY, MAKEWPARAM( nID, ibnDblClk ), (LPARAM)this );
	Window::OnLButtonDblClk(nFlags, point);
}

void ImageBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture();
	_bLeftButtonDown = TRUE;
	Window::OnLButtonDown(nFlags, point);
}

void ImageBox::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CRect rc;
	GetClientRect(&rc);
	if ( _bLeftButtonDown && PtInRect( &rc, point ) )
	{
		int nID = GetDlgCtrlID();
		GetParent()->SendMessage( IBM_NOTIFY, MAKEWPARAM( nID, ibnClick ), (LPARAM)this );
	}
	ReleaseCapture();
	_bLeftButtonDown = FALSE;
	Window::OnLButtonUp(nFlags, point);
}

void ImageBox::OnContextMenu( CWnd * pWnd, CPoint point )
{
	int nID = GetDlgCtrlID();
	GetParent()->SendMessage( IBM_NOTIFY, MAKEWPARAM( nID, ibnContextMenu ), (LPARAM)this );
}

BOOL ImageBox::OnEraseBkgnd(CDC* pDC) 
{
	_CacheImg.OutputEntire( Graphics(*pDC), 0, 0 );

	return TRUE;
}
