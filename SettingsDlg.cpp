// SettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EienLogApp.h"
#include "SettingsDlg.h"
#include "FolderDialog.h"
using namespace Gdiplus;

/////////////////////////////////////////////////////////////////////////////
// CSettingsDlg dialog


CSettingsDlg::CSettingsDlg(CWnd* pParent ) : CDialog(CSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingsDlg)
	_bSaveLogFiles = FALSE;
	_bShowDetail = FALSE;
	_nCacheCount = 0;
	_nLogLength = 0;
	_strSavePath = _T("");
	_strShareName = _T("");
	_nShowCount = 0;
	//}}AFX_DATA_INIT
}


void CSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingsDlg)
	DDX_Check(pDX, IDC_CHECK_SAVE, _bSaveLogFiles);
	DDX_Check(pDX, IDC_CHECK_SHOWDETAIL, _bShowDetail);
	DDX_Text(pDX, IDC_EDIT_CACHE_COUNT, _nCacheCount);
	DDX_Text(pDX, IDC_EDIT_LOG_LENGTH, _nLogLength);
	DDX_Text(pDX, IDC_EDIT_SAVE_PATH, _strSavePath);
	DDX_Text(pDX, IDC_EDIT_SHARE_NAME, _strShareName);
	DDX_Text(pDX, IDC_EDIT_SHOW_COUNT, _nShowCount);
	//}}AFX_DATA_MAP
}

BOOL CSettingsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	IStream * p = CreateStreamFromResource( IDR_PNG_LOGSMALL, TEXT("PNG") );
	_pLogSmallImgStream = p;
	p->Release();

	_pImage = std::auto_ptr<Image>( new Image(_pLogSmallImgStream) );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(CSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CSettingsDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingsDlg message handlers


void CSettingsDlg::OnPaint() 
{
	CPaintDC dc(this);
	Graphics g(dc);
	CRect rc = Window_GetRect( GetDlgItem(IDC_EDIT_SHOW_COUNT)->GetSafeHwnd() );

	g.DrawImage( _pImage.get(), rc.right + 20, 10, _pImage->GetWidth(), _pImage->GetHeight() );
}

void CSettingsDlg::OnButtonBrowse() 
{
	FolderDialog dlg( GetSafeHwnd(), TEXT("请选择一个保存日志的目录") );
	if ( dlg.DoBrowse() )
	{
		_strSavePath = dlg.GetPath().c_str();
		_strSavePath += TEXT("\\");

		UpdateData(FALSE);
	}
}
