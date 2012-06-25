// utils.h: interface for the utils class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UTILS_H__CC4A0943_DFA5_46E4_BA2C_60D59EB89599__INCLUDED_)
#define AFX_UTILS_H__CC4A0943_DFA5_46E4_BA2C_60D59EB89599__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning( disable : 4786 )
#pragma warning( disable : 4244 )

#include <ocidl.h>
#include <shlobj.h>
#include <gdiplus.h>
#include <math.h>
#include <vector>
#include <list>
#include <map>
#include <string>
#include "MemImage.h"
#include "MemDC.h"

// 类型支持 ---------------------------------------------------------------
typedef std::basic_string<CHAR> AnsiString;
typedef AnsiString LocalString;
typedef std::basic_string<WCHAR> UnicodeString;
typedef std::basic_string<TCHAR> String;

typedef std::vector<AnsiString> AnsiStringArray;
typedef std::vector<LocalString> LocalStringArray;
typedef std::vector<UnicodeString> UnicodeStringArray;
typedef std::vector<String> StringArray;

typedef std::list<AnsiString> AnsiStringList;
typedef std::list<LocalString> LocalStringList;
typedef std::list<UnicodeString> UnicodeStringList;
typedef std::list<String> StringList;


// 环境相关 ---------------------------------------------------------------
bool IsExpandString( LPCTSTR lpsz );
String ExplainEnvVars( LPCTSTR lpsz );

// 字串相关 ---------------------------------------------------------------
/* 返回一个字符串里有多少个字符(by local CodePage),用于mbstowcs */
UINT LocalCharsCount( LPCSTR lpszLocal );
/* 返回一个unicode字符串最少长度(by local CodePage),用于wcstombs */
UINT UnicodeMinLength( LPCWSTR lpszUnicode );
/* Unicode转换到本地Ansi */
LocalString UnicodeToLocal( UnicodeString const & strUnicode );
/* 本地ANSI转到Unicode */
UnicodeString LocalToUnicode( LocalString const & strLocal );

/* 兼容字符串与Unicode,Local字符串相互转换 */
String LocalToString( LocalString const & strLocal );
String UnicodeToString( UnicodeString const & strUnicode );
LocalString StringToLocal( String const & str );
UnicodeString StringToUnicode( String const & str );

/* UTF8与兼容串之间的转换 */
String UTF8ToString( AnsiString const & strUTF8 );
AnsiString StringToUTF8( String const & str );

int StrSplit( LPCTSTR lpsz, LPCTSTR lpszDelim, StringArray * pArr );
String StrJoin( LPCTSTR lpszDelim, StringArray const & arr );
String StrInsert( LPCTSTR lpsz, int iStart, int iEnd, LPCTSTR lpsz2 );
String FormatExV( int cchMsg, LPCTSTR lpszFormat, va_list args );
String FormatEx( int cchMsg, LPCTSTR lpszFormat, ... );
String Format( LPCTSTR lpszFormat, ... );

// 资源相关 ---------------------------------------------------------------
/* 载入字符串资源 */
UnicodeString LoadStringResExW( HMODULE hModule, UINT uStringResID );
String LoadStringResEx( HMODULE hModule, UINT uStringResID );
String LoadStringRes( UINT uStringResID );

// 系统相关 ---------------------------------------------------------------
/* 返回模块路径，输出模块文件名 */
String ModulePath( HMODULE hModule = NULL, String * pStrFileName = NULL );
/* 获取路径名 */
String FilePath( String const & strFull, String * pStrFileName = NULL );
/* 获取一个文件名的标题和扩展名 */
String FileTitle( String const & strFileName, String * pStrExtName = NULL );
/* 判断是否是一个目录 */
BOOL IsDirectory( LPCTSTR lpszPath );

/* 获得程序的命令行参数 */
int GetCommandArguments( StringArray * pArr );
/* 使能关机 */
bool ShutdownPrivilege( bool bEnable );

/* 获得描述NT版本的字符串 */
String GetNTVersion( void );
/* 获得描述系统版本的字符串 */
String GetOSVersion( void );
/* 获得自身模块版本号 */
String GetSelfModuleVersion( void );
/* 获得模块版本号 */
String GetModuleVersion( LPCTSTR lpszModuleFile );

// 时间相关 ---------------------------------------------------------------
/* 获得[1970-01-01 0:0:0]到当前的UTC时间,精确到毫秒 */
ULONGLONG GetUTCTimeMS( void );
/* 获得[1970-01-01 0:0:0]到当前的UTC时间,精确到秒 */
UINT GetUTCTime( void );
/* 通过一个[1970-1-1 0:0:0]至今的UTC毫秒数获取一个UTC SYSTEMTIME */
void GetUTCSysTimeByUTCMS( ULONGLONG ullMilliseconds, LPSYSTEMTIME lpSysTime );
/* 通过一个[1970-1-1 0:0:0]至今的UTC毫秒数获取一个Local SYSTEMTIME */
void GetLocalSysTimeByUTCMS( ULONGLONG ullMilliseconds, LPSYSTEMTIME lpSysTime );

// UI相关 -----------------------------------------------------------------
/* 窗口定时器 */
class WindowTimer
{
public:
	WindowTimer( void );
	void Create( HWND hWnd, UINT uElapse );
	void Destroy( void );
	UINT GetID( void ) const;
	~WindowTimer( void );
private:
	HWND _hWnd;
	UINT_PTR _uID;
	static UINT_PTR _uIDAutoIncrement;
	
	WindowTimer( WindowTimer const & );
	WindowTimer & operator = ( WindowTimer const & );
};
// 窗口相关 ---------------------------------------------------------------
/* 弹出一个消息框 */
void MsgBox( String const & strMsg );

/* 获取客户区矩形 */
RECT Window_GetClient( HWND hWnd );
/* 获取窗口矩形,相对于父窗口 */
RECT Window_GetRect( HWND hWnd );
/* 设置窗口矩形,相对于父窗口 */
void Window_SetRect( HWND hWnd, LPCRECT lpRect );
/* 膨胀窗口 */
void Window_Inflate( HWND hWnd, int dx, int dy );
/* 以相对窗口为准居中窗口 */
void Window_Center( HWND hWnd, HWND hRelativeWnd, bool bInRelativeWnd = false );
/* 窗口文本 */
String Window_GetText( HWND hWnd );
void Window_SetText( HWND hWnd, String const & str );

// ListView操作
void ListView_AddStrings( HWND hListView, int nArgCount, ... );
void ListView_InsertStrings( HWND hListView, int iItemIndex, int nArgCount, ... );
void ListView_SetStrings( HWND hListView, int iItemIndex, int nArgCount, ... );
void ListView_GetStrings( HWND hListView, int iItemIndex, int nArgPairCount, ... );

// 图形图像相关 -----------------------------------------------------------
/* 保存位图到指定文件 */
BOOL SaveBitmapToFile( HBITMAP hBitmap, LPCTSTR lpszFileName );

// IPicture
/* 从文件加载图片(bmp,gif,jpg,png),获得IPicture接口,使用者负责释放 */
IPicture * LoadPicture( LPCTSTR lpszPicPath );
/* IPicture * to HBITMAP */
inline HBITMAP PictureGetHBITMAP( IPicture * pIPic )
{
	HBITMAP hBitmap;
	pIPic->get_Handle( (OLE_HANDLE *)&hBitmap );
	return hBitmap;
}

// 与MemDC相关
/* 从文件加载图片(bmp,gif,jpg,png),并获得MemDC对象 */
BOOL LoadPicture( LPCTSTR lpszPicPath, MemDC * pMemDC );

// 与MemImage相关
/* 从文件加载图片(bmp,gif,jpg,png),并获得MemImage对象 */
BOOL LoadPicture( LPCTSTR lpszPicPath, MemImage * pMemImage );

// GDI --------------------------------------------------------------------
/* HIMETRIC转换为设备坐标(即像素) */
void HIMETRICtoDP( HDC hDC, LONG * plX, LONG * plY );
void HIMETRICtoDP( HDC hDC, LPPOINT lpPoint );
/* 设备坐标(即像素)转换为HIMETRIC */
void DPtoHIMETRIC( HDC hDC, LONG * plX, LONG * plY );
void DPtoHIMETRIC( HDC hDC, LPPOINT lpPoint );

// 坐标转换系列函数 -------------------------------------------------------
/* 从缩放到实际 */
template < typename _RECT >
inline _RECT RectFromScale( _RECT const & rect, double scale )
{
	_RECT rc;
	rc.left = rect.left / scale;
	rc.top = rect.top / scale;
	rc.right = rect.right / scale;
	rc.bottom = rect.bottom / scale;
	return rc;
}
template < typename _SIZE >
inline _SIZE SizeFromScale( _SIZE const & si, double scale )
{
	_SIZE si2;
	si2.cx = si.cx / scale;
	si2.cy = si.cy / scale;
	return si2;
}
/* 实际到缩放 */
template < typename _RECT >
inline _RECT RectToScale( _RECT const & rect, double scale )
{
	_RECT rc;
	rc.left = rect.left * scale;
	rc.top = rect.top * scale;
	rc.right = rect.right * scale;
	rc.bottom = rect.bottom * scale;
	return rc;
}
template < typename _SIZE >
inline _SIZE SizeToScale( _SIZE const & si, double scale )
{
	_SIZE si2;
	si2.cx = si.cx * scale;
	si2.cy = si.cy * scale;
	return si2;
}
/* 矩形相交 */
template < typename _RECT >
inline _RECT RectIntersect( _RECT const & rc1, _RECT const & rc2 )
{
	_RECT rc;
	rc.left = rc1.left > rc2.left ? rc1.left : rc2.left;
	rc.top = rc1.top > rc2.top ? rc1.top : rc2.top;
	rc.right = rc1.right < rc2.right ? rc1.right : rc2.right;
	rc.bottom = rc1.bottom < rc2.bottom ? rc1.bottom : rc2.bottom;
	return rc;
}
/* 矩形联合 */
template < typename _RECT >
inline _RECT RectUnion( _RECT const & rc1, _RECT const & rc2 )
{
	_RECT rc;
	rc.left = rc1.left < rc2.left ? rc1.left : rc2.left;
	rc.top = rc1.top < rc2.top ? rc1.top : rc2.top;
	rc.right = rc1.right > rc2.right ? rc1.right : rc2.right;
	rc.bottom = rc1.bottom > rc2.bottom ? rc1.bottom : rc2.bottom;
	return rc;
}
/* 获取一系列矩形有效区 */
template < typename _RECT >
inline _RECT GetValidRect( _RECT const * pArrRect, int nCount )
{
	_RECT rcResult;
	rcResult.left = rcResult.top = rcResult.right = rcResult.bottom = 0;
	if ( nCount < 1 )
	{
		return rcResult;
	}
	rcResult.left = pArrRect[0].left;
	rcResult.top = pArrRect[0].top;
	rcResult.right = pArrRect[0].right;
	rcResult.bottom = pArrRect[0].bottom;
	int i;
	for ( i = 1; i < nCount; ++i )
	{
		_RECT const & rc = pArrRect[i];
		if ( rc.left < rcResult.left )
		{
			rcResult.left = rc.left;
		}
		if ( rc.top < rcResult.top )
		{
			rcResult.top = rc.top;
		}
		if ( rc.right > rcResult.right )
		{
			rcResult.right = rc.right;
		}
		if ( rc.bottom > rcResult.bottom )
		{
			rcResult.bottom = rc.bottom;
		}
	}
	return rcResult;
}

/* 正规化矩形 */
template < typename _RECT >
inline _RECT RectNormalize( _RECT const & rect )
{
	_RECT rcResult = rect;
	if ( rcResult.right < rcResult.left )
	{
		std::swap( rcResult.left, rcResult.right );
	}
	if ( rcResult.bottom < rcResult.top )
	{
		std::swap( rcResult.top, rcResult.bottom );
	}
	return rcResult;
}

/* 矩形宽 */
template < typename _RETVAL, typename _RECT >
inline _RETVAL RectWidth( _RECT const & rc )
{
	return rc.right - rc.left;
}
/* 矩形高 */
template < typename _RETVAL, typename _RECT >
inline _RETVAL RectHeight( _RECT const & rc )
{
	return rc.bottom - rc.top;
}

/* 指定点的外切矩形 */
inline Gdiplus::RectF RectCircumscribePoints( Gdiplus::PointF const points[4] )
{
	Gdiplus::PointF ptNewRectLT, ptNewRectRB;
	ptNewRectLT.X = (((((((((points[0].X) < (points[1].X)) ? (points[0].X) : (points[1].X))) < (points[2].X)) ? ((((points[0].X) < (points[1].X)) ? (points[0].X) : (points[1].X))) : (points[2].X))) < (points[3].X)) ? (((((((points[0].X) < (points[1].X)) ? (points[0].X) : (points[1].X))) < (points[2].X)) ? ((((points[0].X) < (points[1].X)) ? (points[0].X) : (points[1].X))) : (points[2].X))) : (points[3].X));
	ptNewRectLT.Y = (((((((((points[0].Y) < (points[1].Y)) ? (points[0].Y) : (points[1].Y))) < (points[2].Y)) ? ((((points[0].Y) < (points[1].Y)) ? (points[0].Y) : (points[1].Y))) : (points[2].Y))) < (points[3].Y)) ? (((((((points[0].Y) < (points[1].Y)) ? (points[0].Y) : (points[1].Y))) < (points[2].Y)) ? ((((points[0].Y) < (points[1].Y)) ? (points[0].Y) : (points[1].Y))) : (points[2].Y))) : (points[3].Y));
	ptNewRectRB.X = (((((((((points[0].X) > (points[1].X)) ? (points[0].X) : (points[1].X))) > (points[2].X)) ? ((((points[0].X) > (points[1].X)) ? (points[0].X) : (points[1].X))) : (points[2].X))) > (points[3].X)) ? (((((((points[0].X) > (points[1].X)) ? (points[0].X) : (points[1].X))) > (points[2].X)) ? ((((points[0].X) > (points[1].X)) ? (points[0].X) : (points[1].X))) : (points[2].X))) : (points[3].X));
	ptNewRectRB.Y = (((((((((points[0].Y) > (points[1].Y)) ? (points[0].Y) : (points[1].Y))) > (points[2].Y)) ? ((((points[0].Y) > (points[1].Y)) ? (points[0].Y) : (points[1].Y))) : (points[2].Y))) > (points[3].Y)) ? (((((((points[0].Y) > (points[1].Y)) ? (points[0].Y) : (points[1].Y))) > (points[2].Y)) ? ((((points[0].Y) > (points[1].Y)) ? (points[0].Y) : (points[1].Y))) : (points[2].Y))) : (points[3].Y));
	
	return Gdiplus::RectF( ptNewRectLT, Gdiplus::SizeF( ptNewRectRB.X - ptNewRectLT.X, ptNewRectRB.Y - ptNewRectLT.Y ) );
}

/* 旋转之后大小 */
inline SIZE RotateAfterSizes( double angle, int nWidth, int nHeight )
{
	double ang = -angle * acos(0.0f) / 90;
	SIZE si;
	//int newWidth, newHeight;
	double cos_angle = cos(ang);
	double sin_angle = sin(ang);
	
	// Calculate the size of the new bitmap
	POINT p1 = { 0, 0 };
	POINT p2 = { nWidth, 0 };
	POINT p3 = { 0, nHeight };
	POINT p4 = { nWidth - 1, nHeight };
	POINT newP1, newP2, newP3, newP4, leftTop, rightTop, leftBottom, rightBottom;
	
	newP1.x = p1.x;
	newP1.y = p1.y;
	newP2.x = (long)floor( p2.x * cos_angle - p2.y * sin_angle );
	newP2.y = (long)floor( p2.x * sin_angle + p2.y * cos_angle );
	newP3.x = (long)floor( p3.x * cos_angle - p3.y * sin_angle );
	newP3.y = (long)floor( p3.x * sin_angle + p3.y * cos_angle );
	newP4.x = (long)floor( p4.x * cos_angle - p4.y * sin_angle );
	newP4.y = (long)floor( p4.x * sin_angle + p4.y * cos_angle );
	
	leftTop.x = min( min( newP1.x, newP2.x ), min( newP3.x, newP4.x ) );
	leftTop.y = min( min( newP1.y, newP2.y ), min( newP3.y, newP4.y ) );
	rightBottom.x = max( max( newP1.x, newP2.x ), max( newP3.x, newP4.x ) );
	rightBottom.y = max( max( newP1.y, newP2.y ), max( newP3.y, newP4.y ) );
	leftBottom.x = leftTop.x;
	leftBottom.y = 2 + rightBottom.y;
	rightTop.x = 2 + rightBottom.x;
	rightTop.y = leftTop.y;
	
	si.cx = rightTop.x - leftTop.x;
	si.cy = leftBottom.y - leftTop.y;

	return si;
}

inline SIZE RotateAfterSizes( double angle, SIZE const & si )
{
	return RotateAfterSizes( angle, si.cx, si.cy );
}

inline Gdiplus::Size RotateAfterSizes( double angle, Gdiplus::Size const & si )
{
	SIZE siTemp = RotateAfterSizes( angle, si.Width, si.Height );
	return Gdiplus::Size( siTemp.cx, siTemp.cy );
}

/* 点 */
struct GdiPoint
{
	double x;
	double y;
	GdiPoint( double x = 0, double y = 0 ) : x(x), y(y) {}
	explicit GdiPoint( POINT const & pt )
	{
		x = pt.x;
		y = pt.y;
	}
	POINT GetPOINT() const
	{
		POINT pt = { x, y };
		return pt;
	}
};

/* 尺寸 */
struct GdiSize
{
	double cx;
	double cy;
	GdiSize( double cx = 0, double cy = 0 ) : cx(cx), cy(cy) {}
	explicit GdiSize( SIZE const & si )
	{
		cx = si.cx;
		cy = si.cy;
	}
	SIZE GetSIZE() const
	{
		SIZE si = { cx, cy };
		return si;
	}
};

/* 矩形 */
struct GdiRect
{
	double left;
	double top;
	double right;
	double bottom;
	GdiRect( double left = 0, double top = 0, double right = 0, double bottom = 0 ) : left(left), top(top), right(right), bottom(bottom) {}
	GdiRect( GdiPoint const & point, GdiSize const & size ) : left(point.x), top(point.y), right( point.x + size.cx ), bottom( point.y + size.cy ) {}
	GdiRect( GdiPoint const & point1, GdiPoint const & point2 ) : left(point1.x), top(point1.y), right(point2.x), bottom(point2.y) {}
	explicit GdiRect( RECT const & rc )
	{
		left = rc.left;
		top = rc.top;
		right = rc.right;
		bottom = rc.bottom;
	}
	RECT GetRECT() const
	{
		RECT rect = { left, top, right, bottom };
		return rect;
	}
	void OffsetRect( double x, double y )
	{
		left += x;
		right += x;
		top += y;
		bottom += y;
	}
	GdiPoint TopLeft() const
	{
		GdiPoint pt;
		pt.x = left;
		pt.y = top;
		return pt;
	}
	double Width() const { return right - left; }
	double Height() const { return bottom - top; }
	GdiSize Size() const { return GdiSize( Width(), Height() ); }
	BOOL IntersectRect( GdiRect const & rect1, GdiRect const & rect2 )
	{
		*this = RectIntersect( rect1, rect2 );
		GdiSize const & si = Size();
		if ( si.cx > 0 && si.cy > 0 )
		{
			return TRUE;
		}
		return FALSE;
	}
	void UnionRect( GdiRect const & rect1, GdiRect const & rect2 )
	{
		*this = RectUnion( rect1, rect2 );
	}
	BOOL IsRectEmpty() const
	{
		GdiSize const & si = Size();
		return si.cx == 0 || si.cy == 0;
	}
	BOOL PtInRect( GdiPoint const & pt ) const
	{
		if ( pt.x < left || pt.x > right - 1 || pt.y < top || pt.y > bottom - 1 )
		{
			return FALSE;
		}
		return TRUE;
	}
};

/* 固定比例缩放图片到一定范围内,并返回其矩形区域,宽高比,缩放比 */
template < typename _RECT, typename _Type >
inline _RECT ReCalcImageRect( _Type ImageWidth, _Type ImageHeight, _Type Width, _Type Height, double * pRatioWH, double * pScale )
{
	_RECT rectClip;
	*pRatioWH = ImageWidth / (double)ImageHeight; // 宽高比
	if ( ImageWidth <= Width && ImageHeight <= Height ) // 图片小于窗口,不需要缩放,居中即可
	{
		*pScale = 1.0;
		rectClip.left = (Width - ImageWidth) / 2;
		rectClip.right = rectClip.left + ImageWidth;
		rectClip.top = (Height - ImageHeight) / 2;
		rectClip.bottom = rectClip.top + ImageHeight;
	}
	else if ( ImageWidth > Width &&  ImageHeight <= Height ) // 图片比窗口宽,则需要以窗口宽度为准,等比例缩小图片
	{
		*pScale = Width / (double)ImageWidth; // 计算缩放因子
		ImageWidth = Width;
		ImageHeight = ImageWidth / *pRatioWH;
		
		rectClip.left = (Width - ImageWidth) / 2;
		rectClip.right = rectClip.left + ImageWidth;
		rectClip.top = (Height - ImageHeight) / 2;
		rectClip.bottom = rectClip.top + ImageHeight;
	}
	else if ( ImageWidth <= Width && ImageHeight > Height ) // 图片比窗口高
	{
		*pScale = Height / (double)ImageHeight; // 缩放因子
		ImageHeight = Height;
		ImageWidth = ImageHeight * *pRatioWH;
		
		rectClip.left = (Width - ImageWidth) / 2;
		rectClip.right = rectClip.left + ImageWidth;
		rectClip.top = (Height - ImageHeight) / 2;
		rectClip.bottom = rectClip.top + ImageHeight;
	}
	else if ( ImageWidth > Width && ImageHeight > Height ) // 图片宽高都比窗口大
	{
		*pScale = Width / (double)ImageWidth;
		int nTestWidth, nTestHeight;
		nTestWidth = Width;
		nTestHeight = nTestWidth / *pRatioWH;
		if ( nTestHeight > Height )
		{
			*pScale = Height / (double)ImageHeight;
			ImageHeight = Height;
			ImageWidth = ImageHeight * *pRatioWH;
		}
		else
		{
			ImageWidth = nTestWidth;
			ImageHeight = nTestHeight;
		}
		
		rectClip.left = (Width - ImageWidth) / 2;
		rectClip.right = rectClip.left + ImageWidth;
		rectClip.top = (Height - ImageHeight) / 2;
		rectClip.bottom = rectClip.top + ImageHeight;
	}
	return rectClip;
}

/* GDI设备环境对象选入器，自动恢复先前的对象 */
template < typename _GdiObject >
class GdiObjectSelector
{
public:
	GdiObjectSelector( HDC hDC, HGDIOBJ hGdiObject ) : _hDC(hDC), _hGdiObjectOld(NULL)
	{
		_hGdiObjectOld = (_GdiObject)SelectObject( _hDC, hGdiObject );
	}
	~GdiObjectSelector()
	{
		SelectObject( _hDC, _hGdiObjectOld );
	}
private:
	HDC _hDC;
	_GdiObject _hGdiObjectOld;
	GdiObjectSelector( GdiObjectSelector const & );
	GdiObjectSelector & operator = ( GdiObjectSelector const & );
};

// GDI+ -------------------------------------------------------------------
class GdiplusInit
{
	Gdiplus::GdiplusStartupInput _gdiplusStartupInput;
	ULONG_PTR _gdiplusToken;
public:
	GdiplusInit();
	~GdiplusInit();
};
/* 根据MIME获取EncoderClsid */
int GetImageEncoderFromMIME( LPCTSTR lpszMimeType, CLSID * pEncoderClsid );
/* 根据扩展名获取EncoderClsid */
int GetImageEncoderFromExtName( LPCTSTR lpszExtName, CLSID * pEncoderClsid );

/* 将一个COLORREF转换为Color */
inline Gdiplus::Color COLORREFtoColor( COLORREF clr, BYTE alpha = 255 )
{
	return Gdiplus::Color( alpha, GetRValue(clr), GetGValue(clr), GetBValue(clr) );
}
/* 将gdi+的矩形转换到gdi矩形 */
template < typename _RECT, typename _GdipRect >
inline _RECT Rect_GdiplusToGdi( _GdipRect const & rect )
{
	_RECT rc;
	rc.left = rect.GetLeft();
	rc.top = rect.GetTop();
	rc.right = rect.GetRight();
	rc.bottom = rect.GetBottom();
	return rc;
}
/* 将gdi的矩形转换到gdi+矩形 */
template < typename _GdipRect, typename _RECT >
inline _GdipRect Rect_GdiToGdiplus( _RECT const & rect )
{
	_GdipRect rc;
	rc.X = rect.left;
	rc.Y = rect.top;
	rc.Width = rect.right - rect.left;
	rc.Height = rect.bottom - rect.top;
	return rc;
}

// IStream 相关 -----------------------------------------------------------

/* 从磁盘载入文件到内存中,并得到IStream接口指针,使用者负责释放 */
IStream * CreateStreamExistingFile( LPCTSTR lpszFileName );
/* 从指定缓冲区新建一个IStream,使用者负责释放 */
IStream * CreateStreamFromBuffer( LPCVOID lpBuffer, DWORD dwSize );
/* 从资源创建一个IStream,使用者负责释放 */
IStream * CreateStreamFromResourceEx( HMODULE hModule, UINT uResourceID, LPCTSTR lpType );
IStream * CreateStreamFromResource( UINT uResourceID, LPCTSTR lpType );

// 外壳(Shell)相关 --------------------------------------------------------

/* 从一个路径获得ItemIDList,验证存在性 */
LPITEMIDLIST GetItemIDListFromFilePath( String const & strFilePath );
/* 从一个路径获得ItemIDList,不保证存在性 */
LPITEMIDLIST GetSimpleIDListFromPath( String const & strFilePath );
/* 从一个路径获得ItemIDList,可定制 */
HRESULT GetSimpleIDListFromPath( LPWSTR pwszPath, WIN32_FIND_DATAW * pfd, LPITEMIDLIST * ppidl );



#endif // !defined(AFX_UTILS_H__CC4A0943_DFA5_46E4_BA2C_60D59EB89599__INCLUDED_)
