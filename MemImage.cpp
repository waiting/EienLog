// MemImage.cpp: 实现MemImage
//
//////////////////////////////////////////////////////////////////////

#ifdef __GNUC__
#define WINVER 0x0501
#define _WIN32_IE 0x0501
#endif

#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;

#include "MemImage.h"
#include "utils.h"
#include <new>

#pragma comment ( lib, "msimg32" )
#pragma comment ( lib, "gdiplus" )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
MemImage::MemImage( void )
: _pBmpImage(NULL)
{
}

MemImage::MemImage( int nWidth, int nHeight )
{
	new(this) MemImage();
	Create( nWidth, nHeight );
}

MemImage::MemImage( MemImage & other )
{
	new(this) MemImage();
	this->operator = (other);
}

MemImage::~MemImage( void )
{
	Destroy();
}

MemImage & MemImage::operator = ( MemImage const & other )
{
	Clone(other);
	return *this;
}

BOOL MemImage::Create( int nWidth, int nHeight )
{
	Destroy();
	_pBmpImage = new Bitmap( nWidth, nHeight, PixelFormat32bppARGB );
	return _pBmpImage != NULL;
}

BOOL MemImage::Clone( MemImage const & other )
{
	if ( this != &other )
	{
		Destroy();
		_pBmpImage = (Bitmap *)other._pBmpImage->Clone( 0, 0, other.Width(), other.Height(), other._pBmpImage->GetPixelFormat() );
		return TRUE;
	}
	return FALSE;
}

BOOL MemImage::Copy( Image * pImage )
{
	if ( _pBmpImage != pImage )
	{
		Graphics g(_pBmpImage);
		g.DrawImage( pImage, 0, 0, pImage->GetWidth(), pImage->GetHeight() );
		return TRUE;
	}
	return FALSE;
}
void MemImage::Destroy( void )
{
	if ( _pBmpImage )
	{
		delete _pBmpImage;
		_pBmpImage = NULL;
	}
}

BOOL MemImage::PassTo( MemImage & other )
{
	if ( &other != this )
	{
		other.Destroy();
		other._pBmpImage = _pBmpImage;

		_pBmpImage = NULL;
		return TRUE;
	}
	return FALSE;
}

BOOL MemImage::Rotate( double angle, MemImage * pMemImage )
{
	Matrix mat;
	REAL fImageWidth = Width(), fImageHeight = Height();
	mat.RotateAt( angle, PointF( fImageWidth / 2, fImageHeight / 2 ) );
	// 4个顶点
	PointF pt4v[4] = {
		PointF( 0, 0 ),
		PointF( fImageWidth - 0, 0 ),
		PointF( fImageWidth - 0, fImageHeight - 0 ),
		PointF( 0, fImageHeight - 0 )
	};
	PointF pt4v2[4] = {
		PointF( 0, 0 ),
		PointF( fImageWidth - 0, 0 ),
		PointF( fImageWidth - 0, fImageHeight - 0 ),
		PointF( 0, fImageHeight - 0 )
	};
	/*
	printf( "(%f,%f) (%f,%f) (%f,%f) (%f,%f)\n",
			pt4v[0].X, pt4v[0].Y,
			pt4v[1].X, pt4v[1].Y,
			pt4v[2].X, pt4v[2].Y,
			pt4v[3].X, pt4v[3].Y
		);*/
	
	// 算出旋转后4顶点位置
	mat.TransformPoints( pt4v, 4 );
	/*
	printf( "(%f,%f) (%f,%f) (%f,%f) (%f,%f)\n",
			pt4v[0].X, pt4v[0].Y,
			pt4v[1].X, pt4v[1].Y,
			pt4v[2].X, pt4v[2].Y,
			pt4v[3].X, pt4v[3].Y
		);*/
	
	mat.TransformVectors( pt4v2, 4 );
	/*
	printf( "(%f,%f) (%f,%f) (%f,%f) (%f,%f)\n",
			pt4v2[0].X, pt4v2[0].Y,
			pt4v2[1].X, pt4v2[1].Y,
			pt4v2[2].X, pt4v2[2].Y,
			pt4v2[3].X, pt4v2[3].Y
		);*/
	

	// 求出矩形
	RectF rc = RectCircumscribePoints(pt4v);
	// 重新计算旋转矩阵
	mat.Reset();
	mat.RotateAt( angle, PointF( -rc.X + fImageWidth / 2, -rc.Y + fImageHeight / 2 ) );

	pMemImage->Create( rc.Width, rc.Height );
	Graphics g(pMemImage->_pBmpImage);
	g.SetTransform(&mat);
	g.DrawImage( _pBmpImage, -rc.X, -rc.Y, fImageWidth, fImageHeight );

	return TRUE;
}

BOOL MemImage::Stretch( Graphics & gDest, int xDest, int yDest, int nDestWidth, int nDestHeight, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight ) const
{
	return Ok == gDest.DrawImage( _pBmpImage, Rect( xDest, yDest, nDestWidth, nDestHeight ), xSrc, ySrc, nSrcWidth, nSrcHeight, UnitPixel );
}

BOOL MemImage::Output( Graphics & gDest, int xDest, int yDest, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight ) const
{
	return Ok == gDest.DrawImage( _pBmpImage, Rect(xDest, yDest, nSrcWidth, nSrcHeight), xSrc, ySrc, nSrcWidth, nSrcHeight, UnitPixel );
}
