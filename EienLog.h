/****************************************
 *	Eien��־ϵͳ
 *	author: WT
 *	date: 2012-5-22
 ****************************************/
#ifndef __EIENLOG_H__

/* ֪ͨ��־������Ϣ */
#define WM_LOGNOTIFY ( WM_USER + 0x1001 )

#define EIENLOG_EXE TEXT("EienLog.exe")
#define EIENLOG_SHARENAME TEXT("com.x86pro.eienlog")

class EienLog
{
	String _strShareName;
	String _strAppName;
	HANDLE _hMutex;
	HANDLE _hShareMem;
public:
	struct ShareData
	{
		HWND hEienLogWnd; // EienLog������
		int nLogLength; // ������־����
		CHAR szLog[1]; // ��־����
	};
	
	EienLog( LPCTSTR lpszShareName, LPCTSTR lpszAppName = NULL );
	~EienLog();
	
	BOOL Log( String const & strMsg );
	void SetAppName( LPCTSTR lpszAppName );
private:
		ShareData * LockShareMem();
		void UnlockShareMem( ShareData * lpData );
};

#if defined(_DEBUG) || !defined(_DEBUG) && defined(RELEASE_LOG)

extern EienLog __eienlog;

#define EIENLOG(sharename, appname) EienLog __eienlog(sharename, appname);
#define EIENLOG_SETAPPNAME(appname) __eienlog.SetAppName(appname);
#define LOG(msg) __eienlog.Log(msg)

#else

#define EIENLOG(sharename, appname)
#define EIENLOG_SETAPPNAME(appname)
#define LOG(msg)

#endif

#endif // __EIENLOG_H__

