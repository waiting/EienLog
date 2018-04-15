// DetailLogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EienLogApp.h"
#include "DetailLogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDetailLogDlg dialog

CDetailLogDlg::CDetailLogDlg()
{
    //{{AFX_DATA_INIT(CDetailLogDlg)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT

}

void CDetailLogDlg::SetLog( String const & strLog )
{
    _RichEdit.SetWindowText( strLog.c_str() );

    _RichEdit.SetSel( strLog.length(), strLog.length() );
    //CHARRANGE cr;
    //_RichEdit.GetSel(cr);
    //MsgBox( Format("%d,%d",cr));
}

void CDetailLogDlg::DoDataExchange(CDataExchange* pDX)
{
    ModelessDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDetailLogDlg)
    // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDetailLogDlg, ModelessDialog)
    //{{AFX_MSG_MAP(CDetailLogDlg)
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDetailLogDlg message handlers

BOOL CDetailLogDlg::OnInitDialog() 
{
    ModelessDialog::OnInitDialog();
    CRect rc;
    GetClientRect(&rc);
    _RichEdit.CWnd::CreateEx(
        WS_EX_CLIENTEDGE,
        RICHEDIT_CLASS,
        NULL,
        WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_NOHIDESEL | ES_WANTRETURN | ES_MULTILINE,
        rc,
        this,
        IDC_RICHEDIT_DETAILLOG
        );

    CHARFORMAT cf = { sizeof(cf) };
    cf.dwMask = CFM_FACE | CFM_CHARSET;
    strncpy( cf.szFaceName, "ËÎÌו", 4 );
    cf.bCharSet = GB2312_CHARSET;
    _RichEdit.SetDefaultCharFormat(cf);

    //_RichEdit.SetBackgroundColor(FALSE,RGB(49,49,49));

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDetailLogDlg::OnSize(UINT nType, int cx, int cy) 
{
    ModelessDialog::OnSize(nType, cx, cy);
    CRect rc;
    GetClientRect(&rc);

    if ( IsWindow( _RichEdit.GetSafeHwnd() ) )
    {
        _RichEdit.SetWindowPos( NULL, 0, 0, rc.Width(), rc.Height(), SWP_NOMOVE | SWP_NOZORDER );

    }
}
