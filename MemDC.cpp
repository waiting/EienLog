// MemDC.cpp: 实现MemDC
//
//////////////////////////////////////////////////////////////////////

#ifdef __GNUC__
#define WINVER 0x0501
#define _WIN32_IE 0x0501
#endif

#include <windows.h>
#include <gdiplus.h>
#include "MemDC.h"
#include "utils.h"
#include <new>

#pragma comment ( lib, "msimg32" )
#pragma comment ( lib, "gdiplus" )

#ifdef _DEBUG

#include "ximage.h"
#pragma comment(lib, "cximage")
#pragma comment(lib, "jasper")
#pragma comment(lib, "png")
#pragma comment(lib, "jpeg")
#pragma comment(lib, "tiff")
#pragma comment(lib, "zlib")

#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
MemDC::MemDC( void )
: _hMemDC(NULL), _hBitmap(NULL), _nWidth(0), _nHeight(0), _clrBackground(0), _clrTransparent(0), _bIsTransparent(FALSE)
{
}

MemDC::MemDC( HDC hDC )
{
	new(this) MemDC();
	Create(hDC);
}

MemDC::MemDC( HDC hDC, int nWidth, int nHeight, COLORREF clrBackground )
{
	new(this) MemDC();
	Create( hDC, nWidth, nHeight, clrBackground );
}

MemDC::MemDC( MemDC & other )
{
	new(this) MemDC();
	this->operator = (other);
}

MemDC::~MemDC( void )
{
	Destroy();
}

MemDC & MemDC::operator = ( MemDC const & other )
{
	Copy(other);
	return *this;
}

BOOL MemDC::Create( HDC hDC )
{
	Destroy();
	if ( hDC == NULL )
	{
		hDC = GetDC(HWND_DESKTOP);
		_hMemDC = CreateCompatibleDC(hDC);
		ReleaseDC( HWND_DESKTOP, hDC );
	}
	else
	{
		_hMemDC = CreateCompatibleDC(hDC);
	}
	return _hMemDC != NULL;
}

BOOL MemDC::Create( HDC hDC, int nWidth, int nHeight )
{
	if ( !Create(hDC) )
	{
		return FALSE;
	}
	HBITMAP hBitmap;
	if ( hDC == NULL )
	{
		hDC = GetDC(HWND_DESKTOP);
		hBitmap = CreateCompatibleBitmap( hDC, nWidth, nHeight );
		ReleaseDC( HWND_DESKTOP, hDC );
	}
	else
	{
		hBitmap = CreateCompatibleBitmap( hDC, nWidth, nHeight );
	}

	if ( hBitmap == NULL )// 位图创建失败
	{
		DWORD dwError = GetLastError();
		return FALSE;
	}

	AttachBitmap(hBitmap);
	return TRUE;
}

BOOL MemDC::Create( HDC hDC, int nWidth, int nHeight, COLORREF clrBackground )
{
	if ( !Create( hDC, nWidth, nHeight ) )
	{
		return FALSE;
	}
	SetBackground( clrBackground, TRUE );
	return TRUE;
}

BOOL MemDC::Create( HDC hDC, int nWidth, int nHeight, COLORREF clrBackground, COLORREF clrTransparent )
{
	if ( !Create( hDC, nWidth, nHeight, clrBackground ) )
	{
		return FALSE;
	}
	_clrTransparent = clrTransparent;
	_bIsTransparent = TRUE;

	return TRUE;
}

BOOL MemDC::Copy( MemDC const & other )
{
	if ( this != &other )
	{
		Create( other, other.Width(), other.Height() );
		_bIsTransparent = other._bIsTransparent;
		_clrBackground = other._clrBackground;
		_clrTransparent = other._clrTransparent;
		other.CopyToDC( _hMemDC, 0, 0 );
		return TRUE;
	}
	return FALSE;
}

void MemDC::Destroy( void )
{
	if ( _hBitmap )
	{
		DeleteObject(_hBitmap);
	}
	if ( _hMemDC )
	{
		DeleteDC(_hMemDC);
	}
	ZeroMemory( this, sizeof(MemDC) );
}

void MemDC::EnableTransparent( BOOL bIsTransparent, COLORREF clrTransparent /*= 0 */ )
{
	_bIsTransparent = bIsTransparent;
	_clrTransparent = clrTransparent;
}

void MemDC::SetBackground( COLORREF clrBackground, BOOL bFill )
{
	_clrBackground = clrBackground;
	if ( bFill )
	{
		HBRUSH hbr = CreateSolidBrush(clrBackground);
		RECT rc = { 0, 0, _nWidth, _nHeight };
		FillRect( _hMemDC, &rc, hbr ); // 粉刷
		DeleteObject(hbr);
	}

}
HBITMAP MemDC::AttachBitmap( HBITMAP hBitmap )
{
	HBITMAP hOld = DetachBitmap();
	_hBitmap = hBitmap;
	if ( _hMemDC && _hBitmap )
	{
		SelectObject( _hMemDC, _hBitmap );
		BITMAP bm;
		GetObject( _hBitmap, sizeof(BITMAP), &bm );
		_nWidth = bm.bmWidth;
		_nHeight = bm.bmHeight;
	}
	return hOld;
}

HBITMAP MemDC::DetachBitmap( void )
{
	HBITMAP h = _hBitmap;
	_hBitmap = NULL;
	return h;
}

BOOL MemDC::PassTo( MemDC & other )
{
	if ( &other != this )
	{
		other.Destroy();
		other._bIsTransparent = _bIsTransparent;
		other._clrBackground = _clrBackground;
		other._clrTransparent = _clrTransparent;
		other._hBitmap = _hBitmap;
		other._hMemDC = _hMemDC;
		other._nHeight = _nHeight;
		other._nWidth = _nWidth;
		ZeroMemory( this, sizeof(MemDC) );
	}
	return FALSE;
}

BOOL MemDC::RotateGdiplus( double angle, MemDC * pMemDC )
{
	using namespace Gdiplus;
	Bitmap bmp( _hBitmap, NULL );
	REAL fImageWidth = bmp.GetWidth(), fImageHeight = bmp.GetHeight();
	Matrix mat;
	mat.Translate( fImageWidth / 2, fImageHeight / 2 );
	mat.Rotate(angle);
	mat.Translate( -fImageWidth / 2, -fImageHeight / 2 );
	// 4个顶点
	PointF pt4v[4] = {
		PointF( 0, 0 ),
		PointF( fImageWidth - 0, 0 ),
		PointF( fImageWidth - 0, fImageHeight - 0 ),
		PointF( 0, fImageHeight - 0 )
	};
	// 算出旋转后4顶点位置
	mat.TransformPoints( pt4v, 4 );
	// 求出矩形
	RectF rcf = RectCircumscribePoints(pt4v);
	// 重新计算旋转矩阵
	mat.Reset();
	mat.Translate( -rcf.X + fImageWidth / 2, -rcf.Y + fImageHeight / 2 );
	mat.Rotate(angle);
	mat.Translate( -( -rcf.X + fImageWidth / 2 ), -( -rcf.Y + fImageHeight / 2 ) );
	// 生成新图
	pMemDC->Create( _hMemDC, rcf.Width, rcf.Height, _clrBackground );
	pMemDC->EnableTransparent( _bIsTransparent, _clrTransparent );

	Graphics g(*pMemDC);
	g.SetTransform(&mat);

	if ( _bIsTransparent )
	{
		RectF rcDest( -rcf.X, -rcf.Y, fImageWidth, fImageHeight );
		ImageAttributes imgattr;
		Color clr( GetRValue(_clrTransparent), GetGValue(_clrTransparent), GetBValue(_clrTransparent) );
		imgattr.SetColorKey( clr, clr );
		g.DrawImage( &bmp, rcDest, 0, 0, fImageWidth, fImageHeight, UnitPixel, &imgattr );
	}
	else
	{
		g.DrawImage( &bmp, -rcf.X, -rcf.Y, fImageWidth, fImageHeight );
	}

	g.ResetTransform();
	return TRUE;
}

#ifdef _DEBUG
BOOL MemDC::RotateCxImage( double angle, MemDC * pMemDC )
{
	CxImage img;
	img.CreateFromHBITMAP(_hBitmap);

	if ( _bIsTransparent )
	{
		img.SetTransIndex(0);
		RGBQUAD rgb = { 0 };
		rgb.rgbRed = GetRValue(_clrTransparent);
		rgb.rgbGreen = GetGValue(_clrTransparent);
		rgb.rgbBlue = GetBValue(_clrTransparent);
		img.SetTransColor(rgb);
	}

	SIZE si = RotateAfterSizes( angle, Width(), Height() );
	pMemDC->Create( _hMemDC, si.cx, si.cy, _clrBackground );
	pMemDC->EnableTransparent( _bIsTransparent, _clrTransparent );

	img.Rotate(angle);
	img.Draw2(*pMemDC);

	return TRUE;
}
#endif

BOOL MemDC::StretchBlt( HDC hDestDC, int xDest, int yDest, int nDestWidth, int nDestHeight, int x, int y, int width, int height, int nMode /*= HALFTONE */ ) const
{
	if ( _hMemDC == NULL )
	{
		return FALSE;
	}
	nMode = SetStretchBltMode( hDestDC, nMode );
	BOOL b = ::StretchBlt( hDestDC, xDest, yDest, nDestWidth, nDestHeight, _hMemDC, x, y, width, height, SRCCOPY );
	SetStretchBltMode( hDestDC, nMode );
	return b;
}

BOOL MemDC::StretchToDC( HDC hDestDC, int xDest, int yDest, int nDestWidth, int nDestHeight, int nMode ) const
{
	return StretchBlt( hDestDC, xDest, yDest, nDestWidth, nDestHeight, 0, 0, _nWidth, _nHeight, nMode );
}

BOOL MemDC::BitBlt( HDC hDestDC, int xDest, int yDest, int nDestWidth, int nDestHeight, int x, int y ) const
{
	if ( _hMemDC == NULL )
	{
		return FALSE;
	}
	return ::BitBlt( hDestDC, xDest, yDest, nDestWidth, nDestHeight, _hMemDC, x, y, SRCCOPY );
}

BOOL MemDC::CopyToDC( HDC hDestDC, int xDest, int yDest ) const
{
	return BitBlt( hDestDC, xDest, yDest, _nWidth, _nHeight, 0, 0 );
}

BOOL MemDC::TransparentBlt( HDC hDestDC, int xDest, int yDest, int nDestWidth, int nDestHeight, int x, int y, int width, int height, int nMode /*= HALFTONE */ ) const
{
	if ( _hMemDC == NULL )
	{
		return FALSE;
	}
	nMode = SetStretchBltMode( hDestDC, nMode );
	BOOL b;
	if ( IsTransparent() )
	{
		b = ::TransparentBlt( hDestDC, xDest, yDest, nDestWidth, nDestHeight, _hMemDC, x, y, width, height, (UINT)_clrTransparent );
	}
	else
	{
		b = ::StretchBlt( hDestDC, xDest, yDest, nDestWidth, nDestHeight, _hMemDC, x, y, width, height, SRCCOPY );
	}
	SetStretchBltMode( hDestDC, nMode );
	return b;
}

BOOL MemDC::TransparentToDC( HDC hDestDC, int xDest, int yDest, int nDestWidth, int nDestHeight, int nMode /*= HALFTONE */ ) const
{
	return TransparentBlt( hDestDC, xDest, yDest, nDestWidth, nDestHeight, 0, 0, _nWidth, _nHeight, nMode );
}

