// LogListBox.cpp : implementation file
//

#include "stdafx.h"
#include "EienLogApp.h"
#include "LogListBox.h"
using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// LogListBox

LogListBox::LogListBox()
{
}

LogListBox::~LogListBox()
{
}


BEGIN_MESSAGE_MAP(LogListBox, CListBox)
    //{{AFX_MSG_MAP(LogListBox)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LogListBox message handlers

void LogListBox::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
    Graphics g( GetSafeHwnd() );
    CString strData;
    UnicodeString wstr;
    Rect rcBackground = Rect_GdiToGdiplus<Rect>(lpDrawItemStruct->rcItem);
    Color clrBgDefault = COLORREFtoColor( lpDrawItemStruct->itemID != (UINT)-1 && lpDrawItemStruct->itemID % 2 ? 0xF9F9F9 : GetSysColor(COLOR_WINDOW) );
    Color clrBgSelected = COLORREFtoColor( 0xE4BEA5/*GetSysColor(COLOR_HIGHLIGHT)*/ );
    SolidBrush brushBgDefault(clrBgDefault);
    SolidBrush brushBgSelected(clrBgSelected);
    Pen penBoder(Color::LightGray);

    if ( lpDrawItemStruct->itemAction & ODA_DRAWENTIRE )
    {
        g.FillRectangle( &brushBgDefault, rcBackground );
    }

    if ( lpDrawItemStruct->itemState & ODS_SELECTED )
    {
        g.FillRectangle( &brushBgSelected, rcBackground );
    }
    else
    {
        g.FillRectangle( &brushBgDefault, rcBackground );
    }

    if ( lpDrawItemStruct->itemID != (UINT)-1 )
    {
        Rect rc = rcBackground;
        rc.Width -= 1;
        rc.Height -= 1;
        g.DrawLine( &penBoder, rc.GetLeft(), rc.GetBottom(), rc.GetRight(), rc.GetBottom() );
    }

    if ( lpDrawItemStruct->itemState & ODS_FOCUS )
    {
        Pen pen( Color::Black );
        Rect rc = rcBackground;
        rc.Width -= 1;
        rc.Height -= 1;
        pen.SetDashStyle(DashStyleDot);
        g.DrawRectangle( &pen, rc );
    }

    if ( lpDrawItemStruct->itemID != (UINT)-1 )
        GetText(lpDrawItemStruct->itemID, strData );

    wstr = StringToUnicode( (LPCTSTR)strData );

    RectF rc = RectF( rcBackground.X, rcBackground.Y, rcBackground.Width, rcBackground.Height );
    rc.Inflate( -2, -2 );
    StringFormat sf;
    g.DrawString(
        wstr.c_str(), 
        wstr.length(),
        &Font( L"Lucida Console", 11 ),
        rc,
        &sf,
        &SolidBrush(Color::Black)
        );
}

void LogListBox::MeasureItem( LPMEASUREITEMSTRUCT lpMeasureItemStruct ) 
{
    lpMeasureItemStruct->itemHeight *= 3;

}
