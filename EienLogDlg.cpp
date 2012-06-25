// EienLogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EienLogApp.h"
#include "EienLog.h"
#include "EienLogDlg.h"
#include "SettingsDlg.h"
#include <time.h>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CEienLogDlg dialog

CEienLogDlg::CEienLogDlg( CWnd * pParent ) : CDialog(CEienLogDlg::IDD, pParent), _IniFile( ( ModulePath() + _T('\\') + LoadStringRes(IDS_STRING_INIFILE) ).c_str() )
{
	//{{AFX_DATA_INIT(CEienLogDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	_bShareNameFromCMD = FALSE;

	_settings.bSaveLogFiles = FALSE;
	_settings.bShowDetail = FALSE;
	_settings.nCacheCount = 1000;
	_settings.nLogLength = 2048;
	_settings.nShowCount = 500;
	_settings.strSavePath = _T(".\\");
	_settings.strShareName = LoadStringRes(IDS_STRING_SHARENAME);

	_strIniFileSection = LoadStringRes(IDS_STRING_INIFILE_SECTION);

	_hShareMem = NULL;
	_hMutex = NULL;

}

CEienLogDlg::~CEienLogDlg()
{
	FreeShareData();
	SaveLogFiles();
}

void CEienLogDlg::CreateShareData()
{
	FreeShareData();

	String strMutexName = _settings.strShareName + _T("/mutex");
	String strShareMem = _settings.strShareName + _T("/sharemem");
	_hMutex = CreateMutex( NULL, FALSE, strMutexName.c_str() );
	_hShareMem = CreateFileMapping( INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(EienLog::ShareData) + _settings.nLogLength, strShareMem.c_str() );

	EienLog::ShareData * lpData = LockShareMem();
	lpData->hEienLogWnd = GetSafeHwnd();
	lpData->nLogLength = _settings.nLogLength;
	ZeroMemory( lpData->szLog, _settings.nLogLength + 1 );
	UnlockShareMem(lpData);

}

void CEienLogDlg::FreeShareData()
{
	if ( _hShareMem )
		CloseHandle(_hShareMem);
	if ( _hMutex )
		CloseHandle(_hMutex);
	
}

EienLog::ShareData * CEienLogDlg::LockShareMem()
{
	return (EienLog::ShareData *)MapViewOfFile( _hShareMem, FILE_MAP_ALL_ACCESS, 0, 0, 0 );
}

void CEienLogDlg::UnlockShareMem( EienLog::ShareData * lpData )
{
	UnmapViewOfFile(lpData);
}

void CEienLogDlg::UpdateUI()
{
	if ( _DetailLogDlg )
	{
		if ( _settings.bShowDetail )
		{
			CRect rc;
			GetWindowRect(&rc);
			_DetailLogDlg.SetWindowPos( NULL, rc.left + rc.Width(), rc.top, rc.Height(), rc.Height(), SWP_NOZORDER );
			_DetailLogDlg.ShowWindow(SW_NORMAL);
		}
		else
		{
			_DetailLogDlg.ShowWindow(SW_HIDE);
		}
	}
}

void CEienLogDlg::SaveLogFiles()
{
	if ( !_settings.bSaveLogFiles )
		return;

	String strSavePath = _settings.strSavePath + Format( "eienlog_%I64u", GetUTCTimeMS() ) + ".log";

	std::ofstream fout( strSavePath.c_str() );
	int i;
	for ( i = 0; i < _LogsCache.size(); i++ )
	{
		fout << _LogsCache[i] << std::endl;
	}
}

void CEienLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEienLogDlg)
	//DDX_Control(pDX, IDC_LIST_LOGS, _LogListBox);
	//}}AFX_DATA_MAP
}

BOOL CEienLogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	//SetIcon(m_hIcon, FALSE);		// Set small icon

	CRect rcThis = Window_GetClient( GetSafeHwnd() );
	CRect rcButton = Window_GetRect( GetDlgItem(IDC_BUTTON_SETTINGS)->GetSafeHwnd() );

	_LogListBox.CreateEx(
		WS_EX_CLIENTEDGE,
		"LISTBOX",
		NULL,
		WS_VSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE | LBS_HASSTRINGS | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED,
		CRect( 5, 5, rcThis.right - 5, rcButton.top - 6 ),
		this,
		IDC_LIST_LOGS
	);
	//_LogListBox.SetFont( GetFont() );

	_settings.bSaveLogFiles = _IniFile.GetValue( _strIniFileSection.c_str(), _T("SaveLogFiles"), _settings.bSaveLogFiles );
	_settings.bShowDetail = _IniFile.GetValue( _strIniFileSection.c_str(), _T("ShowDetail"), _settings.bShowDetail );
	_settings.nCacheCount = _IniFile.GetValue( _strIniFileSection.c_str(), _T("CacheCount"), _settings.nCacheCount );
	_settings.nLogLength = _IniFile.GetValue( _strIniFileSection.c_str(), _T("LogLength"), _settings.nLogLength );
	_settings.nShowCount = _IniFile.GetValue( _strIniFileSection.c_str(), _T("ShowCount"), _settings.nShowCount );
	_settings.strSavePath = _IniFile.GetValue( _strIniFileSection.c_str(), _T("SavePath"), _settings.strSavePath.c_str() );
	if ( !_bShareNameFromCMD )
		_settings.strShareName = _IniFile.GetValue( _strIniFileSection.c_str(), _T("ShareName"), _settings.strShareName.c_str() );

	_DetailLogDlg.AutoDelete(FALSE);
	_DetailLogDlg.Create( CDetailLogDlg::IDD, this );
	_DetailLogDlg.UpdateWindow();

	CreateShareData();

	SetWindowText( Format( _T("%s[%s(%s)]"), LoadStringRes(IDS_STRING_CAPTION).c_str(), _bShareNameFromCMD ? "command" : "settings", _settings.strShareName.c_str() ).c_str() );

	return TRUE;  // return TRUE  unless you set the focus to a control
}


BEGIN_MESSAGE_MAP(CEienLogDlg, CDialog)
	//{{AFX_MSG_MAP(CEienLogDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SETTINGS, OnButtonSettings)
	ON_MESSAGE(WM_LOGNOTIFY, OnLogNotify)
	ON_WM_MOVE()
	ON_LBN_SELCHANGE(IDC_LIST_LOGS, OnSelChangeListLogs)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEienLogDlg message handlers

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEienLogDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEienLogDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}

void CEienLogDlg::OnButtonSettings() 
{
	CSettingsDlg dlg(this);
	dlg._bSaveLogFiles = _settings.bSaveLogFiles;
	dlg._bShowDetail = _settings.bShowDetail;
	dlg._nCacheCount = _settings.nCacheCount;
	dlg._nLogLength = _settings.nLogLength;
	dlg._nShowCount = _settings.nShowCount;
	dlg._strSavePath = _settings.strSavePath.c_str();
	dlg._strShareName = _settings.strShareName.c_str();

	if ( dlg.DoModal() == IDOK )
	{
		_settings.bSaveLogFiles = dlg._bSaveLogFiles;
		_settings.bShowDetail = dlg._bShowDetail;
		_settings.nCacheCount = dlg._nCacheCount;
		_settings.nLogLength = dlg._nLogLength;
		_settings.nShowCount = dlg._nShowCount;
		_settings.strSavePath = (LPCTSTR)dlg._strSavePath;
		_settings.strShareName = (LPCTSTR)dlg._strShareName;
		_IniFile.SetValue( _strIniFileSection.c_str(), _T("SaveLogFiles"), _settings.bSaveLogFiles );
		_IniFile.SetValue( _strIniFileSection.c_str(), _T("ShowDetail"), _settings.bShowDetail );
		_IniFile.SetValue( _strIniFileSection.c_str(), _T("CacheCount"), _settings.nCacheCount );
		_IniFile.SetValue( _strIniFileSection.c_str(), _T("LogLength"), _settings.nLogLength );
		_IniFile.SetValue( _strIniFileSection.c_str(), _T("ShowCount"), _settings.nShowCount );
		_IniFile.SetValue( _strIniFileSection.c_str(), _T("SavePath"), _settings.strSavePath.c_str() );
		_IniFile.SetValue( _strIniFileSection.c_str(), _T("ShareName"), _settings.strShareName.c_str() );

		MessageBox( TEXT("重启程序改变的设置才生效"), NULL, MB_ICONWARNING );
	}
}

LRESULT CEienLogDlg::OnLogNotify( WPARAM wParam, LPARAM lParam )
{
	String strLog;
	EienLog::ShareData * lpData;

	lpData = LockShareMem();
	strLog = lpData->szLog;
	ZeroMemory( lpData->szLog, strLog.length() );
	UnlockShareMem(lpData);

	if ( _LogListBox.GetCount() == _settings.nShowCount )
	{
		_LogListBox.DeleteString(0);
	}
	if ( _LogsShow.size() == _settings.nShowCount )
	{
		_LogsShow.erase( _LogsShow.begin() );
	}
	_LogListBox.AddString( strLog.c_str() );
	_LogsShow.push_back(strLog);

	_LogListBox.SetCurSel( _LogListBox.GetCount() - 1 );

	if ( _settings.bShowDetail ) _DetailLogDlg.SetLog(strLog);

	if ( _LogsCache.size() == _settings.nCacheCount )
	{
		SaveLogFiles();
		_LogsCache.clear();
	}
	_LogsCache.push_back(strLog);


	return 0;
}


void CEienLogDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	CRect rc;
	GetWindowRect(&rc);
	_DetailLogDlg && _DetailLogDlg.SetWindowPos( NULL, rc.left + rc.Width(), rc.top, rc.Height(), rc.Height(), SWP_NOZORDER );

}

void CEienLogDlg::OnSelChangeListLogs() 
{
	int iSel = _LogListBox.GetCurSel();
	if ( iSel == -1 ) return;

	if ( _settings.bShowDetail ) _DetailLogDlg.SetLog( _LogsShow[iSel] );

}

void CEienLogDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if ( bShow )
	{
		UpdateUI();
	}
}
