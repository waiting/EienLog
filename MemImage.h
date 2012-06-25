// MemImage.h: interface for the MemImage class.
// �ڴ�ͼƬ,�������,֧��alphaͨ��.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMIMAGE_H__A58D0E0E_5BA5_4C98_846D_DBD012F54199__INCLUDED_)
#define AFX_MEMIMAGE_H__A58D0E0E_5BA5_4C98_846D_DBD012F54199__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MemImage
{
public:

	MemImage( void );
	MemImage( int nWidth, int nHeight );
	MemImage( MemImage & other );
	~MemImage( void );

	MemImage & operator = ( MemImage const & other );
	operator BOOL() const { return _pBmpImage != NULL; }
	operator Gdiplus::Bitmap * () const { return _pBmpImage; }

	int Width( void ) const { return _pBmpImage ? _pBmpImage->GetWidth() : 0; }
	int Height( void ) const { return _pBmpImage ? _pBmpImage->GetHeight() : 0; }

	BOOL Create( int nWidth, int nHeight );
	BOOL Create( Gdiplus::Size const & size ) { return Create( size.Width, size.Height ); };
	void Destroy( void );
	BOOL Clone( MemImage const & other );
	BOOL Copy( Gdiplus::Image * pImage );
	/* ���ݹ���Ȩ,�Լ�����������Դ */
	BOOL PassTo( MemImage & other );
	/* �����ĵ���תangle�Ƕ� */
	BOOL Rotate( double angle, MemImage * pMemImage );

	BOOL Stretch( Gdiplus::Graphics & gDest, int xDest, int yDest, int nDestWidth, int nDestHeight, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight ) const;
	BOOL StretchEntire( Gdiplus::Graphics & gDest, int xDest, int yDest, int nDestWidth, int nDestHeight ) const
	{
		return Stretch( gDest, xDest, yDest, nDestWidth, nDestHeight, 0, 0, Width(), Height() );
	}
	BOOL Output( Gdiplus::Graphics & gDest, int xDest, int yDest, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight ) const;
	BOOL OutputEntire( Gdiplus::Graphics & gDest, int xDest, int yDest ) const
	{
		return Output( gDest, xDest, yDest, 0, 0, Width(), Height() );
	}

	BOOL Stretch( MemImage & imgDest, int xDest, int yDest, int nDestWidth, int nDestHeight, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight ) const
	{
		if ( this != &imgDest )
		{
			return Stretch( Gdiplus::Graphics(imgDest._pBmpImage), xDest, yDest, nDestWidth, nDestHeight, xSrc, ySrc, nSrcWidth, nSrcHeight );
		}
		return FALSE;
	}
	BOOL StretchEntire( MemImage & imgDest, int xDest, int yDest, int nDestWidth, int nDestHeight ) const
	{
		return Stretch( imgDest, xDest, yDest, nDestWidth, nDestHeight, 0, 0, Width(), Height() );
	}
	BOOL Output( MemImage & imgDest, int xDest, int yDest, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight ) const
	{
		if ( this != &imgDest )
		{
			return Output( Gdiplus::Graphics(imgDest._pBmpImage), xDest, yDest, xSrc, ySrc, nSrcWidth, nSrcHeight );
		}
		return FALSE;
	}
	BOOL OutputEntire( MemImage & imgDest, int xDest, int yDest ) const
	{
		return Output( imgDest, xDest, yDest, 0, 0, Width(), Height() );
	}

private:
	Gdiplus::Bitmap * _pBmpImage;
};

#endif // !defined(AFX_MEMIMAGE_H__A58D0E0E_5BA5_4C98_846D_DBD012F54199__INCLUDED_)
