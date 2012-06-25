// utils.cpp: implementation of the utils class.
//
//////////////////////////////////////////////////////////////////////
#ifdef __GNUC__
#define WINVER 0x0501
#define _WIN32_IE 0x0501
#endif

#define _WIN32_WINNT 0x0501

#include <algorithm>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <commctrl.h>
#include <olectl.h>
//#include <strsafe.h>
#include "utils.h"
#pragma comment ( lib, "gdiplus" )
#pragma comment ( lib, "Version.lib" )

// <WinNT.h> --------------------------------------------------------------
// Product types
// This list grows with each OS release.
//
// There is no ordering of values to ensure callers
// do an equality test i.e. greater-than and less-than
// comparisons are not useful.
//
// NOTE: Values in this list should never be deleted.
//       When a product-type 'X' gets dropped from a
//       OS release onwards, the value of 'X' continues
//       to be used in the mapping table of GetProductInfo.
//
#define PRODUCT_UNDEFINED                           0x00000000

#define PRODUCT_ULTIMATE                            0x00000001
#define PRODUCT_HOME_BASIC                          0x00000002
#define PRODUCT_HOME_PREMIUM                        0x00000003
#define PRODUCT_ENTERPRISE                          0x00000004
#define PRODUCT_HOME_BASIC_N                        0x00000005
#define PRODUCT_BUSINESS                            0x00000006
#define PRODUCT_STANDARD_SERVER                     0x00000007
#define PRODUCT_DATACENTER_SERVER                   0x00000008
#define PRODUCT_SMALLBUSINESS_SERVER                0x00000009
#define PRODUCT_ENTERPRISE_SERVER                   0x0000000A
#define PRODUCT_STARTER                             0x0000000B
#define PRODUCT_DATACENTER_SERVER_CORE              0x0000000C
#define PRODUCT_STANDARD_SERVER_CORE                0x0000000D
#define PRODUCT_ENTERPRISE_SERVER_CORE              0x0000000E
#define PRODUCT_ENTERPRISE_SERVER_IA64              0x0000000F
#define PRODUCT_BUSINESS_N                          0x00000010
#define PRODUCT_WEB_SERVER                          0x00000011
#define PRODUCT_CLUSTER_SERVER                      0x00000012
#define PRODUCT_HOME_SERVER                         0x00000013
#define PRODUCT_STORAGE_EXPRESS_SERVER              0x00000014
#define PRODUCT_STORAGE_STANDARD_SERVER             0x00000015
#define PRODUCT_STORAGE_WORKGROUP_SERVER            0x00000016
#define PRODUCT_STORAGE_ENTERPRISE_SERVER           0x00000017
#define PRODUCT_SERVER_FOR_SMALLBUSINESS            0x00000018
#define PRODUCT_SMALLBUSINESS_SERVER_PREMIUM        0x00000019
#define PRODUCT_HOME_PREMIUM_N                      0x0000001A
#define PRODUCT_ENTERPRISE_N                        0x0000001B
#define PRODUCT_ULTIMATE_N                          0x0000001C
#define PRODUCT_WEB_SERVER_CORE                     0x0000001D
#define PRODUCT_MEDIUMBUSINESS_SERVER_MANAGEMENT    0x0000001E
#define PRODUCT_MEDIUMBUSINESS_SERVER_SECURITY      0x0000001F
#define PRODUCT_MEDIUMBUSINESS_SERVER_MESSAGING     0x00000020
#define PRODUCT_SERVER_FOUNDATION                   0x00000021
#define PRODUCT_HOME_PREMIUM_SERVER                 0x00000022
#define PRODUCT_SERVER_FOR_SMALLBUSINESS_V          0x00000023
#define PRODUCT_STANDARD_SERVER_V                   0x00000024
#define PRODUCT_DATACENTER_SERVER_V                 0x00000025
#define PRODUCT_ENTERPRISE_SERVER_V                 0x00000026
#define PRODUCT_DATACENTER_SERVER_CORE_V            0x00000027
#define PRODUCT_STANDARD_SERVER_CORE_V              0x00000028
#define PRODUCT_ENTERPRISE_SERVER_CORE_V            0x00000029
#define PRODUCT_HYPERV                              0x0000002A
#define PRODUCT_STORAGE_EXPRESS_SERVER_CORE         0x0000002B
#define PRODUCT_STORAGE_STANDARD_SERVER_CORE        0x0000002C
#define PRODUCT_STORAGE_WORKGROUP_SERVER_CORE       0x0000002D
#define PRODUCT_STORAGE_ENTERPRISE_SERVER_CORE      0x0000002E
#define PRODUCT_STARTER_N                           0x0000002F
#define PRODUCT_PROFESSIONAL                        0x00000030
#define PRODUCT_PROFESSIONAL_N                      0x00000031
#define PRODUCT_SB_SOLUTION_SERVER                  0x00000032
#define PRODUCT_SERVER_FOR_SB_SOLUTIONS             0x00000033
#define PRODUCT_STANDARD_SERVER_SOLUTIONS           0x00000034
#define PRODUCT_STANDARD_SERVER_SOLUTIONS_CORE      0x00000035
#define PRODUCT_SB_SOLUTION_SERVER_EM               0x00000036
#define PRODUCT_SERVER_FOR_SB_SOLUTIONS_EM          0x00000037
#define PRODUCT_SOLUTION_EMBEDDEDSERVER             0x00000038
#define PRODUCT_SOLUTION_EMBEDDEDSERVER_CORE        0x00000039
#define PRODUCT_SMALLBUSINESS_SERVER_PREMIUM_CORE   0x0000003F
#define PRODUCT_ESSENTIALBUSINESS_SERVER_MGMT       0x0000003B
#define PRODUCT_ESSENTIALBUSINESS_SERVER_ADDL       0x0000003C
#define PRODUCT_ESSENTIALBUSINESS_SERVER_MGMTSVC    0x0000003D
#define PRODUCT_ESSENTIALBUSINESS_SERVER_ADDLSVC    0x0000003E
#define PRODUCT_CLUSTER_SERVER_V                    0x00000040
#define PRODUCT_EMBEDDED                            0x00000041
#define PRODUCT_STARTER_E                           0x00000042
#define PRODUCT_HOME_BASIC_E                        0x00000043
#define PRODUCT_HOME_PREMIUM_E                      0x00000044
#define PRODUCT_PROFESSIONAL_E                      0x00000045
#define PRODUCT_ENTERPRISE_E                        0x00000046
#define PRODUCT_ULTIMATE_E                          0x00000047

#define PRODUCT_UNLICENSED                          0xABCDABCD

#define VER_SERVER_NT                       0x80000000
#define VER_WORKSTATION_NT                  0x40000000
#define VER_SUITE_SMALLBUSINESS             0x00000001
#define VER_SUITE_ENTERPRISE                0x00000002
#define VER_SUITE_BACKOFFICE                0x00000004
#define VER_SUITE_COMMUNICATIONS            0x00000008
#define VER_SUITE_TERMINAL                  0x00000010
#define VER_SUITE_SMALLBUSINESS_RESTRICTED  0x00000020
#define VER_SUITE_EMBEDDEDNT                0x00000040
#define VER_SUITE_DATACENTER                0x00000080
#define VER_SUITE_SINGLEUSERTS              0x00000100
#define VER_SUITE_PERSONAL                  0x00000200
#define VER_SUITE_BLADE                     0x00000400
#define VER_SUITE_EMBEDDED_RESTRICTED       0x00000800
#define VER_SUITE_SECURITY_APPLIANCE        0x00001000
#define VER_SUITE_STORAGE_SERVER            0x00002000
#define VER_SUITE_COMPUTE_SERVER            0x00004000
#define VER_SUITE_WH_SERVER                 0x00008000

// <WinUser.h> ------------------------------------------------------------
#if(_WIN32_WINNT >= 0x0501)
#define SM_STARTER              88
#define SM_SERVERR2             89
#endif /* _WIN32_WINNT >= 0x0501 */


// 环境相关 ---------------------------------------------------------------
bool IsExpandString( LPCTSTR lpsz )
{
	LPCTSTR p = lpsz;
	int i = 0, j;
	while ( p[i] )
	{
		if ( p[i] == '%' )
		{
			j = i + 1;
			while ( p[j] && p[j] != '%' ) j++;
			if ( p[j] != 0 )
			{
				i = j + 1;
				return true;
			}
		}
		else
		{
			i++;
		}
	}
	return false;
}

String ExplainEnvVars( LPCTSTR lpsz )
{
	//TCHAR sz[0x7FFFU] = {0};
	//ExpandEnvironmentStrings( lpsz, sz, 0x7FFFU );
	//return sz;
	String strRes;
	String str(lpsz);
	LPCTSTR p = lpsz;
	int i = 0, j;
	while ( p[i] )
	{
		if ( p[i] == '%' )
		{
			j = i + 1;
			while ( p[j] && p[j] != '%' ) j++;
			if ( p[j] == 0 )
			{
				strRes += str.substr( i, j - i );
				i = j;
			}
			else
			{
				String strEnvVar = str.substr( i + 1, j - i - 1 );
				strEnvVar = _tgetenv( strEnvVar.c_str() );
				strRes += strEnvVar;
				i = j + 1;
			}
		}
		else
		{
			strRes += p[i];
			i++;
		}
	}
	return strRes;//*/
}


// 字串相关 ---------------------------------------------------------------
UINT LocalCharsCount( LPCSTR lpszLocal )
{
	UINT uCount = 0;
	uCount = MultiByteToWideChar(
		CP_ACP,
		MB_PRECOMPOSED | MB_USEGLYPHCHARS,
		lpszLocal,
		lstrlenA(lpszLocal),
		NULL,
		0
	);
	return uCount;
}

UINT UnicodeMinLength( LPCWSTR lpszUnicode )
{
	UINT uLength = 0;
	uLength = WideCharToMultiByte(
		CP_ACP,
		WC_SEPCHARS | WC_COMPOSITECHECK,
		lpszUnicode,
		lstrlenW(lpszUnicode),
		NULL,
		0,
		NULL,
		NULL
	);
	return uLength;
}

LocalString UnicodeToLocal( UnicodeString const & strUnicode )
{
	LocalString str;
	UINT uLength = UnicodeMinLength( strUnicode.c_str() );
	str.resize(uLength);
	WideCharToMultiByte(
		CP_ACP,
		WC_SEPCHARS | WC_COMPOSITECHECK,
		strUnicode.c_str(),
		strUnicode.length(),
		&str[0],
		uLength,
		NULL,
		NULL
	);
	return str;
}

UnicodeString LocalToUnicode( LocalString const & strLocal )
{
	UnicodeString str;
	UINT uCount = LocalCharsCount( strLocal.c_str() );
	str.resize(uCount);
	MultiByteToWideChar(
		CP_ACP,
		MB_PRECOMPOSED | MB_USEGLYPHCHARS,
		strLocal.c_str(),
		strLocal.length(),
		&str[0],
		uCount
	);
	return str;
}

String LocalToString( LocalString const & strLocal )
{
#ifdef UNICODE
	return LocalToUnicode(strLocal);
#else
	return strLocal;
#endif
}

String UnicodeToString( UnicodeString const & strUnicode )
{
#ifdef UNICODE
	return strUnicode;
#else
	return UnicodeToLocal(strUnicode);
#endif
}

LocalString StringToLocal( String const & str )
{
#ifdef UNICODE
	return UnicodeToLocal(str);
#else
	return str;
#endif
}

UnicodeString StringToUnicode( String const & str )
{
#ifdef UNICODE
	return str;
#else
	return LocalToUnicode(str);
#endif
}

String UTF8ToString( AnsiString const & strUTF8 )
{
	UnicodeString strUnicode;
	int cch = MultiByteToWideChar(
		CP_UTF8,
		0,
		strUTF8.c_str(),
		strUTF8.length(),
		NULL,
		0
	);
	strUnicode.resize(cch);
	MultiByteToWideChar(
		CP_UTF8,
		0,
		strUTF8.c_str(),
		strUTF8.length(),
		&strUnicode[0],
		cch
	);
	return UnicodeToString(strUnicode);
}

AnsiString StringToUTF8( String const & str )
{
	UnicodeString strUnicode = StringToUnicode(str);
	AnsiString strUTF8;
	int nLength = WideCharToMultiByte(
		CP_UTF8,
		0,
		strUnicode.c_str(),
		strUnicode.length(),
		NULL,
		0,
		NULL,
		NULL
	);
	strUTF8.resize(nLength);
	WideCharToMultiByte(
		CP_UTF8,
		0,
		strUnicode.c_str(),
		strUnicode.length(),
		&strUTF8[0],
		nLength,
		NULL,
		NULL
	);
	return strUTF8;
}


int StrSplit( LPCTSTR lpsz, LPCTSTR lpszDelim, StringArray * pArr )
{
	TCHAR * pszDup;
	TCHAR * pszToken;
	int nCount;
	pszDup = _tcsdup(lpsz);
	pszToken = _tcstok( pszDup, lpszDelim );
	nCount = 0;
	while ( pszToken != NULL )
	{
		nCount++;
		if ( pArr != NULL ) pArr->push_back(pszToken);
		pszToken = _tcstok( NULL, lpszDelim );
	}
	free(pszDup);
	return nCount;
}

String StrJoin( LPCTSTR lpszDelim, StringArray const & arr )
{
	String strRes;
	int nCount = arr.size();
	int i;
	for ( i = 0; i < nCount; i++ )
	{
		if ( i != 0 )
		{
			strRes += lpszDelim;
		}
		strRes += arr[i];
	}
	return strRes;
}

String StrInsert( LPCTSTR lpsz, int iStart, int iEnd, LPCTSTR lpsz2 )
{
	String strRes;
	String str(lpsz);
	strRes += str.substr( 0, iStart );
	strRes += lpsz2;
	if ( iEnd < str.length() )
		strRes += str.substr( iEnd );
	return strRes;
}

String FormatExV( int cchMsg, LPCTSTR lpszFormat, va_list args )
{
	String str;
	str.resize(cchMsg);
	_vsntprintf( &str[0], cchMsg, lpszFormat, args );
	return str.c_str();
}

String FormatEx( int cchMsg, LPCTSTR lpszFormat, ... )
{
	va_list args;
	va_start( args, lpszFormat );
	return FormatExV( cchMsg, lpszFormat, args );
}

String Format( LPCTSTR lpszFormat, ... )
{
	va_list args;
	va_start( args, lpszFormat );
	return FormatExV( 1024, lpszFormat, args );
}

// 资源相关 ---------------------------------------------------------------
UnicodeString LoadStringResExW( HMODULE hModule, UINT uStringResID )
{
	UnicodeString strRes;
	WORD wBlockID = ( uStringResID >> 4 ) + 1;
	WORD wStrResIndex = uStringResID % 16;
	HRSRC hRSRC = FindResource( hModule, MAKEINTRESOURCE(wBlockID), RT_STRING );
	if ( hRSRC != NULL )
	{
		DWORD dwSize = SizeofResource( hModule, hRSRC );
		HGLOBAL hResource = LoadResource( hModule, hRSRC );
		LPBYTE pData = (LPBYTE)LockResource(hResource);
		DWORD dwOffset = 0;
		int iIndex = 0;
		while ( dwOffset + sizeof(WORD) <= dwSize )
		{
			WORD w = *(WORD *)( pData + dwOffset );
			dwOffset += sizeof(WORD);
			if ( w > 0 )
			{
				if ( iIndex == wStrResIndex )
				{
					UnicodeString strUnicode;
					strUnicode.resize(w);
					CopyMemory( &strUnicode[0], pData + dwOffset, w * sizeof(WCHAR) );
					strRes = strUnicode.c_str();
					break;
				}
				dwOffset += w * sizeof(WCHAR);
			}
			iIndex++;
		}
		FreeResource(hResource);
	}
	return strRes;
}

String LoadStringResEx( HMODULE hModule, UINT uStringResID )
{
	return UnicodeToString( LoadStringResExW( hModule, uStringResID ) );
}

String LoadStringRes( UINT uStringResID )
{
	return LoadStringResEx( GetModuleHandle(NULL), uStringResID );
}

// 系统相关 ---------------------------------------------------------------
String ModulePath( HMODULE hModule /*= NULL*/, String * pStrFileName /*= NULL */ )
{
	String strBuffer;
	strBuffer.resize(MAX_PATH);
	GetModuleFileName( hModule, &strBuffer[0], MAX_PATH );
	return FilePath( strBuffer, pStrFileName );
}

String FilePath( String const & strFull, String * pStrFileName /*= NULL */ )
{
	String strPath;
	String strBuffer = strFull.c_str();
	TCHAR * psz = _tcsrchr( &strBuffer[0], _T('\\') );
	TCHAR * pszFile;
	if ( psz != NULL )
	{
		*psz = 0;
		strPath = &strBuffer[0];
		if ( pStrFileName != NULL ) *pStrFileName = psz + 1;
		pszFile = psz + 1;
	}
	else
	{
		strPath = TEXT("");
		if ( pStrFileName != NULL ) *pStrFileName = &strBuffer[0];
		pszFile = &strBuffer[0];
	}
	return strPath;
}

String FileTitle( String const & strFileName, String * pStrExtName /*= NULL */ )
{
	String strFileNameTemp = strFileName;
	String strFileTitle;
	TCHAR * pszFile = &strFileNameTemp[0];
	TCHAR * psz;
	psz = _tcsrchr( pszFile, _T('.') );
	if ( psz != NULL )
	{
		*psz = 0;
		strFileTitle = pszFile;
		if ( pStrExtName != NULL ) *pStrExtName = psz + 1;
	}
	else
	{
		strFileTitle = pszFile;
		if ( pStrExtName != NULL ) *pStrExtName = TEXT("");
	}
	return strFileTitle;
}

/* 判断是否是一个目录 */
BOOL IsDirectory( LPCTSTR lpszPath )
{
	DWORD dwAttr = GetFileAttributes(lpszPath);
	if ( dwAttr != INVALID_FILE_ATTRIBUTES && dwAttr & FILE_ATTRIBUTE_DIRECTORY )
	{
		return TRUE;
	}
	return FALSE;
}


int GetCommandArguments( StringArray * pArr )
{
	pArr->clear();
	// 命令行参数处理
	LPWSTR lpszCmdLine = GetCommandLineW();
	int nNumArgs, i;
	LPWSTR * pArgsArr = CommandLineToArgvW( lpszCmdLine, &nNumArgs );
	for ( i = 0; i < nNumArgs; ++i )
	{
		pArr->push_back( UnicodeToString( pArgsArr[i] ) );
	}
	GlobalFree( (HGLOBAL)pArgsArr );
	return nNumArgs;
}

bool ShutdownPrivilege( bool bEnable )
{
	HANDLE hToken;
	bool bRet = OpenProcessToken( GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken ) != FALSE;
	if ( !bRet ) return FALSE;
	TOKEN_PRIVILEGES tp;
	tp.PrivilegeCount = 1;
	LookupPrivilegeValue( NULL, SE_SHUTDOWN_NAME, &tp.Privileges[0].Luid );
	tp.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : 0;
	AdjustTokenPrivileges( hToken, FALSE, &tp, 0, NULL, NULL );
	bRet = ( GetLastError() == ERROR_SUCCESS );
	CloseHandle(hToken);
	return bRet;
}

String GetNTVersion( void )
{
	String strVer;
	OSVERSIONINFO osvi;
	SYSTEM_INFO si;
	ZeroMemory( &osvi, sizeof(OSVERSIONINFO) );
	ZeroMemory( &si, sizeof(SYSTEM_INFO) );
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	
	if ( !GetVersionEx(&osvi) )
		return _T("");

	if ( osvi.dwPlatformId == VER_PLATFORM_WIN32s ) // Win32s on Windows 3.1.
	{
		strVer = _T("Windows 3.1 ");
	}
	else if ( osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS ) // Windows 95, Windows 98, or Windows Me.
	{
		strVer = _T("Windows ");
	}
	else // */
	if ( osvi.dwPlatformId == VER_PLATFORM_WIN32_NT ) // Windows NT, Windows 2000, Windows XP, or Windows Server 2003 family.
	{
		strVer = _T("Windows NT ");
	}

	strVer += Format( _T("%u.%u.%u"), osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber );

	return strVer;
}

String GetOSVersion( void )
{
	String strVer;
	typedef void (WINAPI * PGNSI)(LPSYSTEM_INFO);
	typedef BOOL (WINAPI * PGPI)( DWORD, DWORD, DWORD, DWORD, PDWORD );
	OSVERSIONINFOEX osvi;
	SYSTEM_INFO si;
	PGNSI pGNSI;
	PGPI pGPI;
	BOOL bOsVersionInfoEx;
	DWORD dwType;

	ZeroMemory( &si, sizeof(SYSTEM_INFO) );
	ZeroMemory( &osvi, sizeof(OSVERSIONINFOEX) );

	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	if( !( bOsVersionInfoEx = GetVersionEx( (OSVERSIONINFO *)&osvi ) ) )
		return _T("");

	// Call GetNativeSystemInfo if supported or GetSystemInfo otherwise.
	pGNSI = (PGNSI)GetProcAddress( GetModuleHandle( _T("kernel32.dll") ), "GetNativeSystemInfo" );
	if( NULL != pGNSI )
		pGNSI(&si);
	else
		GetSystemInfo(&si);

	strVer += _T("Microsoft ");

	if ( VER_PLATFORM_WIN32_NT == osvi.dwPlatformId && osvi.dwMajorVersion > 4 )
	{
		// Test for the specific product.

		if ( osvi.dwMajorVersion == 6 )
		{
			if( osvi.dwMinorVersion == 0 )
			{
				if( osvi.wProductType == VER_NT_WORKSTATION )
					strVer += _T("Windows Vista ");  
				else
					strVer += _T("Windows Server 2008 ");  
			}
			else if ( osvi.dwMinorVersion == 1 )
			{
				if( osvi.wProductType == VER_NT_WORKSTATION )
					strVer += _T("Windows 7 ");
				else
					strVer += _T("Windows Server 2008 R2 ");
			}

			pGPI = (PGPI)GetProcAddress(
				GetModuleHandle( _T("kernel32.dll") ),
				"GetProductInfo"
			);

			pGPI( osvi.dwMajorVersion, osvi.dwMinorVersion, 0, 0, &dwType);

			switch( dwType )
			{
			case PRODUCT_ULTIMATE:
				strVer += _T("Ultimate Edition");
				break;
			case PRODUCT_PROFESSIONAL:
				strVer += _T("Professional");
				break;
			case PRODUCT_HOME_PREMIUM:
				strVer += _T("Home Premium Edition");
				break;
			case PRODUCT_HOME_BASIC:
				strVer += _T("Home Basic Edition");
				break;
			case PRODUCT_ENTERPRISE:
				strVer += _T("Enterprise Edition");
				break;
			case PRODUCT_BUSINESS:
				strVer += _T("Business Edition");
				break;
			case PRODUCT_STARTER:
				strVer += _T("Starter Edition");
				break;
			case PRODUCT_CLUSTER_SERVER:
				strVer += _T("Cluster Server Edition");
				break;
			case PRODUCT_DATACENTER_SERVER:
				strVer += _T("Datacenter Edition");
				break;
			case PRODUCT_DATACENTER_SERVER_CORE:
				strVer += _T("Datacenter Edition (core installation)");
				break;
			case PRODUCT_ENTERPRISE_SERVER:
				strVer += _T("Enterprise Edition");
				break;
			case PRODUCT_ENTERPRISE_SERVER_CORE:
				strVer += _T("Enterprise Edition (core installation)");
				break;
			case PRODUCT_ENTERPRISE_SERVER_IA64:
				strVer += _T("Enterprise Edition for Itanium-based Systems");
				break;
			case PRODUCT_SMALLBUSINESS_SERVER:
				strVer += _T("Small Business Server");
				break;
			case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM:
				strVer += _T("Small Business Server Premium Edition");
				break;
			case PRODUCT_STANDARD_SERVER:
				strVer += _T("Standard Edition");
				break;
			case PRODUCT_STANDARD_SERVER_CORE:
				strVer += _T("Standard Edition (core installation)");
				break;
			case PRODUCT_WEB_SERVER:
				strVer += _T("Web Server Edition");
				break;
			}
		}
		else if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2 )
		{
			if( GetSystemMetrics(SM_SERVERR2) )
				strVer += _T("Windows Server 2003 R2 ");
			else if ( osvi.wSuiteMask & VER_SUITE_STORAGE_SERVER )
				strVer += _T("Windows Storage Server 2003 ");
			else if ( osvi.wSuiteMask & VER_SUITE_WH_SERVER )
				strVer += _T("Windows Home Server ");
			else if( osvi.wProductType == VER_NT_WORKSTATION && si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 )
				strVer += _T("Windows XP Professional x64 Edition");
			else
				strVer += _T("Windows Server 2003 ");

			// Test for the server type.
			if ( osvi.wProductType != VER_NT_WORKSTATION )  
			{
				if ( si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64 )
				{
					if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
						strVer += _T("Datacenter Edition for Itanium-based Systems");
					else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
						strVer += _T("Enterprise Edition for Itanium-based Systems");
				}
				else if ( si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 )
				{
					if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
						strVer += _T("Datacenter x64 Edition");
					else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
						strVer += _T("Enterprise x64 Edition");
					else
						strVer += _T("Standard x64 Edition");
				}
				else  
				{  
					if ( osvi.wSuiteMask & VER_SUITE_COMPUTE_SERVER )
						strVer += _T("Compute Cluster Edition");
					else if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
						strVer += _T("Datacenter Edition");
					else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
						strVer += _T("Enterprise Edition");
					else if ( osvi.wSuiteMask & VER_SUITE_BLADE )
						strVer += _T("Web Edition");
					else
						strVer += _T("Standard Edition");
				}
			}
		}
		else if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1 )
		{
			strVer += _T("Windows XP ");
			if( osvi.wSuiteMask & VER_SUITE_PERSONAL )
				strVer += _T("Home Edition");
			else
				strVer += _T("Professional");
		}
		else if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 )
		{
			strVer += _T("Windows 2000 ");
			if ( osvi.wProductType == VER_NT_WORKSTATION )
			{
				strVer += _T("Professional");
			}
			else
			{
				if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
					strVer += _T("Datacenter Server");
				else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
					strVer += _T("Advanced Server");
				else
					strVer += _T("Server");
			}
		}

		// Include service pack (if any) and build number.  
		if( _tcslen(osvi.szCSDVersion) > 0 )  
		{  
			strVer += _T(" ");
			strVer += osvi.szCSDVersion;
		}

		strVer += Format( TEXT(" (build %d)"), osvi.dwBuildNumber );

		if ( osvi.dwMajorVersion >= 6 )
		{
			if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64 )
				strVer += TEXT(" 64-bit");
			else if (si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_INTEL )
				strVer += _T(" 32-bit");
		}
	}
	else
	{
		strVer += _T("Windows 9x or lower");
	}


	return strVer;
}

String GetSelfModuleVersion( void )
{
	String strFullPath;
	strFullPath = ModulePath( NULL, &strFullPath ) + _T("\\") + strFullPath;
	return GetModuleVersion( strFullPath.c_str() );
}

String GetModuleVersion( LPCTSTR lpszModuleFile )
{
	String strVer;
	DWORD dwVerInfoSize = 0;
	DWORD dwVerHnd;
	VS_FIXEDFILEINFO * pFileInfo;

	dwVerInfoSize = GetFileVersionInfoSize( lpszModuleFile, &dwVerHnd );
	if ( dwVerInfoSize )
	{
		// If we were able to get the information, process it:
		HANDLE hMem;
		LPVOID lpvMem;
		UINT uInfoSize = 0;
		WORD nProdVersion[4];

		hMem = GlobalAlloc( GMEM_MOVEABLE, dwVerInfoSize );
		lpvMem = GlobalLock(hMem);
		GetFileVersionInfo( lpszModuleFile, dwVerHnd, dwVerInfoSize, lpvMem );
		::VerQueryValue( lpvMem, TEXT("\\"), (LPVOID *)&pFileInfo, &uInfoSize);
		//根据参数的不同，可以获取不同的文件版本信息
		// Product version from the FILEVERSION of the version info resource
		nProdVersion[0] = HIWORD(pFileInfo->dwFileVersionMS);
		nProdVersion[1] = LOWORD(pFileInfo->dwFileVersionMS);
		nProdVersion[2] = HIWORD(pFileInfo->dwFileVersionLS);
		nProdVersion[3] = LOWORD(pFileInfo->dwFileVersionLS);
		strVer = Format(
			TEXT("%hu.%hu.%hu.%hu"),
			nProdVersion[0],
			nProdVersion[1],
			nProdVersion[2],
			nProdVersion[3]
		);

		GlobalUnlock(hMem);
		GlobalFree(hMem);
	}

	return strVer;
}
//-------------------------------------------------------------------------
// 1970-01-01 00:00:00的ULARGE_INTEGER描述
static ULARGE_INTEGER __Time1970( void )
{
	SYSTEMTIME st1970 = {0};
	st1970.wYear = 1970;
	st1970.wMonth = 1;
	st1970.wDay = 1;
	st1970.wHour = 0;
	st1970.wMinute = 0;
	st1970.wSecond = 0;
	
	FILETIME ft1970;
	ULARGE_INTEGER time1970;
	SystemTimeToFileTime( &st1970, &ft1970 );
	CopyMemory( &time1970, &ft1970, sizeof(time1970) );
	return time1970;
}

ULONGLONG GetUTCTimeMS( void )
{
	SYSTEMTIME st;
	FILETIME ft;
	ULARGE_INTEGER time;
	GetSystemTime(&st);
	SystemTimeToFileTime( &st, &ft );
	CopyMemory( &time, &ft, sizeof(time) );
	
	ULARGE_INTEGER timeRes;
	timeRes.QuadPart = time.QuadPart - __Time1970().QuadPart;
	
	return timeRes.QuadPart / 10000;
}

UINT GetUTCTime( void )
{
	return (UINT)( GetUTCTimeMS() / 1000 );
}

void GetUTCSysTimeByUTCMS( ULONGLONG ullMilliseconds, LPSYSTEMTIME lpSysTime )
{
	ULONGLONG ullTime = ullMilliseconds * 10000;
	ULARGE_INTEGER time;
	time.QuadPart = ullTime + __Time1970().QuadPart;
	FILETIME ft;
	CopyMemory( &ft, &time, sizeof(ft) );
	FileTimeToSystemTime( &ft, lpSysTime );
}

void GetLocalSysTimeByUTCMS( ULONGLONG ullMilliseconds, LPSYSTEMTIME lpSysTime )
{
	ULONGLONG ullTime = ullMilliseconds * 10000;
	ULARGE_INTEGER time;
	time.QuadPart = ullTime + __Time1970().QuadPart;
	FILETIME ft,localft;
	CopyMemory( &ft, &time, sizeof(ft) );
	FileTimeToLocalFileTime( &ft, &localft );
	FileTimeToSystemTime( &localft, lpSysTime );
}

// UI相关 -----------------------------------------------------------------
UINT_PTR WindowTimer::_uIDAutoIncrement = 0;
WindowTimer::WindowTimer( void ) : _hWnd(NULL), _uID(0)
{
}

WindowTimer::~WindowTimer( void )
{
	Destroy();
}

void WindowTimer::Create( HWND hWnd, UINT uElapse )
{
	Destroy();
	_hWnd = hWnd;
	if ( _hWnd )
	{
		_uID = ++_uIDAutoIncrement;
		SetTimer( _hWnd, _uID, uElapse, NULL );
	}
}

void WindowTimer::Destroy( void )
{
	if ( _hWnd )
	{
		KillTimer( _hWnd, _uID );
		_hWnd = NULL;
	}
}

UINT WindowTimer::GetID( void ) const
{
	return _uID;
}

// 窗口相关 ---------------------------------------------------------------
void MsgBox( String const & strMsg )
{
	MessageBox( GetForegroundWindow(), strMsg.c_str(), _T("Information Box"), 0 );
}
/* 获取客户区矩形 */
RECT Window_GetClient( HWND hWnd )
{
	RECT rc;
	GetClientRect( hWnd, &rc );
	return rc;
}

RECT Window_GetRect( HWND hWnd )
{
	RECT rc;
	GetWindowRect( hWnd, &rc );
	HWND hParentWnd;
	hParentWnd = GetParent(hWnd);
	if ( IsWindow(hParentWnd) )
	{
		ScreenToClient( hParentWnd, (LPPOINT)&rc );
		ScreenToClient( hParentWnd, (LPPOINT)&rc + 1 );
	}
	return rc;
}

void Window_SetRect( HWND hWnd, LPCRECT lpRect )
{
	SetWindowPos( hWnd, NULL, lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top, SWP_NOZORDER );
}

void Window_Inflate( HWND hWnd, int dx, int dy )
{
	RECT rc = Window_GetRect(hWnd);
	InflateRect( &rc, dx, dy );
	Window_SetRect( hWnd, &rc );
}

void Window_Center( HWND hWnd, HWND hRelativeWnd, bool bInRelativeWnd )
{
	INT cx, cy, offsetLeft, offsetTop;
	if ( hRelativeWnd && IsWindow(hRelativeWnd) )
	{
		if ( bInRelativeWnd )
		{
			RECT rcWnd;
			GetClientRect( hRelativeWnd, &rcWnd );
			cx = rcWnd.right - rcWnd.left;
			cy = rcWnd.bottom - rcWnd.top;
			offsetLeft = 0;//rcWnd.left;
			offsetTop = 0;//rcWnd.top;
		}
		else
		{
			RECT rcWnd;
			GetWindowRect( hRelativeWnd, &rcWnd );
			cx = rcWnd.right - rcWnd.left;
			cy = rcWnd.bottom - rcWnd.top;
			offsetLeft = rcWnd.left;
			offsetTop = rcWnd.top;
		}
	}
	else // use screen coord
	{
		cx = GetSystemMetrics(SM_CXSCREEN);
		cy = GetSystemMetrics(SM_CYSCREEN);
		offsetLeft = 0;
		offsetTop = 0;
	}
	RECT rc;
	GetWindowRect( hWnd, &rc );
	LONG nWidth = rc.right - rc.left;
	LONG nHeight = rc.bottom - rc.top;
	INT left, top;
	left = offsetLeft + ( cx - nWidth ) / 2;
	top = offsetTop + ( cy - nHeight ) / 2;
	SetWindowPos( hWnd, NULL, left, top, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
}

String Window_GetText( HWND hWnd )
{
	String strRes;
	int nLen = GetWindowTextLength(hWnd);
	strRes.resize(nLen);
	GetWindowText( hWnd, &strRes[0], nLen + 1 );
	return strRes.c_str();
}

void Window_SetText( HWND hWnd, String const & str )
{
	SetWindowText( hWnd, str.c_str() );
}


// ListView操作
void ListView_AddStrings( HWND hListView, int nArgCount, ... )
{
	int nItemsCount = ListView_GetItemCount(hListView);
	int nColCount = Header_GetItemCount( ListView_GetHeader(hListView) );
	LVITEM item;
	item.mask = LVIF_TEXT;
	item.iItem = nItemsCount;
	item.iSubItem = 0;
	item.pszText = (LPTSTR)NULL;
	item.state = 0;
	item.stateMask = 0;
	item.iImage = 0;
	item.lParam = 0;
	ListView_InsertItem( hListView, &item );
	va_list vaArgList;
	va_start( vaArgList, nArgCount );
	for ( int i = 0; i < nArgCount && i < nColCount; i++ )
	{
		LPTSTR lpsz = va_arg( vaArgList, LPTSTR );
		ListView_SetItemText( hListView, nItemsCount, i, lpsz );
	}
	va_end(vaArgList);
}

void ListView_InsertStrings( HWND hListView, int iItemIndex, int nArgCount, ... )
{
	int nColCount = Header_GetItemCount( ListView_GetHeader(hListView) );
	LVITEM item;
	item.mask = LVIF_TEXT;
	item.iItem = iItemIndex;
	item.iSubItem = 0;
	item.pszText = (LPTSTR)NULL;
	item.state = 0;
	item.stateMask = 0;
	item.iImage = 0;
	item.lParam = 0;
	ListView_InsertItem( hListView, &item );

	va_list vaArglist;
	va_start( vaArglist, nArgCount );
	for ( int i = 0; i < nArgCount && i < nColCount; i++ )
	{
		LPTSTR lpsz = va_arg( vaArglist, LPTSTR );
		ListView_SetItemText( hListView, iItemIndex, i, lpsz );
	}
	va_end(vaArglist);
}

void ListView_SetStrings( HWND hListView, int iItemIndex, int nArgCount, ... )
{
	int nColCount = Header_GetItemCount( ListView_GetHeader(hListView) );
	va_list vaArgList;
	va_start( vaArgList, nArgCount );
	for ( int i = 0; i < nArgCount && i < nColCount; i++ )
	{
		LPTSTR lpsz = va_arg( vaArgList, LPTSTR );
		ListView_SetItemText( hListView, iItemIndex, i, lpsz );
	}
	va_end(vaArgList);

}

void ListView_GetStrings( HWND hListView, int iItemIndex, int nArgPairCount, ... )
{
	int nColCount = Header_GetItemCount( ListView_GetHeader(hListView) );
	va_list vaArgList;
	va_start( vaArgList, nArgPairCount );
	for ( int i = 0; i < nArgPairCount && i < nColCount; i++ )
	{
		LPTSTR lpsz = va_arg( vaArgList, LPTSTR );
		int cch = va_arg( vaArgList, int );
		if ( lpsz != NULL )
		{
			ListView_GetItemText( hListView, iItemIndex, i, lpsz, cch );
		}
	}
	va_end(vaArgList);
}

// 图形图像相关 -----------------------------------------------------------
BOOL SaveBitmapToFile( HBITMAP hBitmap, LPCTSTR lpszFileName )
{
	HDC hDC; //设备描述表
	int nBits;  //当前显示分辨率下每个像素所占位数
	WORD wBitCount = 0;    //位图中每个像素所占位数
	//调色板大小，位图中像素字节大小，位图文件大小，写入文件字节数
	DWORD dwPaletteSize = 0, dwBmBitsSize, dwDIBSize, dwWritten;
	BITMAP bitmap; //位图属性
	BITMAPFILEHEADER bmfHdr; //位图文件头
	BITMAPINFOHEADER bi;//位图信息头
	LPBITMAPINFOHEADER lpbi; //指向位图信息头
	//文件句柄，分配内存句柄，调色板句柄
	HANDLE hFile, hDibData;
	HPALETTE hPal, hOldPal = NULL;
	//计算位图文件每个像素所占位数
	hDC = CreateDC( TEXT("DISPLAY"), NULL, NULL, NULL );
	nBits = GetDeviceCaps( hDC, BITSPIXEL ) * GetDeviceCaps( hDC, PLANES );
	DeleteDC(hDC);
	if ( nBits <= 1 )
		wBitCount = 1;
	else if ( nBits <= 4 )
		wBitCount = 4;
	else if ( nBits <= 8 )
		wBitCount = 8;
	else if ( nBits <= 24 )
		wBitCount = 24;
	else
		wBitCount = 32;
	//计算调色板大小，4,8位位图，需建立调色板
	if ( wBitCount <= 8 )
		dwPaletteSize = ( 1 << wBitCount ) * sizeof(RGBQUAD);

	//设置位图信息头
	GetObject( hBitmap, sizeof(BITMAP), &bitmap );
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bitmap.bmWidth;
	bi.biHeight = bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;
	//计算像素数据字节数
	dwBmBitsSize = ( ( bitmap.bmWidth * wBitCount + 31 ) / 32 ) * 4 * bitmap.bmHeight;
	//为位图内容分配内存
	hDibData = GlobalAlloc( GHND, dwBmBitsSize + dwPaletteSize + sizeof( BITMAPINFOHEADER ) );
	lpbi = ( LPBITMAPINFOHEADER )GlobalLock( hDibData );
	*lpbi = bi;
	//处理调色板      
	hPal = ( HPALETTE )GetStockObject(DEFAULT_PALETTE);
	if ( hPal )
	{
		hDC = GetDC(NULL);
		hOldPal = SelectPalette( hDC, hPal, FALSE );
		RealizePalette(hDC);
	}
	//获取该调色板下新的像素值
	GetDIBits( hDC, hBitmap, 0, (UINT)bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize, (LPBITMAPINFO)lpbi, DIB_RGB_COLORS );
	//恢复调色板
	if (hOldPal)
	{
		SelectPalette(hDC, hOldPal, TRUE);
		RealizePalette(hDC);
		ReleaseDC(NULL, hDC);
	}
	//创建位图文件
	hFile = CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;
	//设置位图文件头
	bmfHdr.bfType = 0x4D42; //"BM"
	dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
	//写入位图文件头
	WriteFile(hFile, &bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	//写入位图文件其余内容
	WriteFile(hFile, lpbi, dwDIBSize, &dwWritten, NULL);
	//清除
	GlobalUnlock(hDibData);
	GlobalFree(hDibData);
	CloseHandle(hFile);
	return TRUE;
}

IPicture * LoadPicture( LPCTSTR lpszPicPath )
{
	HRESULT hr;
	IPicture * pIPicture = NULL;
	IStream * pStream = CreateStreamExistingFile(lpszPicPath);
	if ( pStream == NULL )
	{
		return NULL;
	}
	hr = OleLoadPicture( pStream, 0, FALSE, IID_IPicture, (LPVOID *)&pIPicture );
	pStream->Release();
	if ( FAILED(hr) ) // 创建IPicture接口失败,返回null
	{
		return NULL;
	}

	return pIPicture;
}

BOOL LoadPicture( LPCTSTR lpszPicPath, MemImage * pMemImage )
{
	Gdiplus::Bitmap bmp( StringToUnicode(lpszPicPath).c_str() );
	pMemImage->Create( bmp.GetWidth(), bmp.GetHeight() );
	pMemImage->Copy(&bmp);
	return TRUE;
}

BOOL LoadPicture( LPCTSTR lpszPicPath, MemDC * pMemDC )
{
	IPicture * pIPic;
	if ( ( pIPic = LoadPicture(lpszPicPath) ) != NULL )
	{
		HDC hDC = GetDC(HWND_DESKTOP);
		MemDC TempDC;
		HBITMAP hBitmap = PictureGetHBITMAP(pIPic);
		TempDC.Create(hDC);
		TempDC.AttachBitmap(hBitmap);
		pMemDC->Copy(TempDC);
		TempDC.DetachBitmap();
		ReleaseDC( HWND_DESKTOP, hDC );
		pIPic->Release();

		return TRUE;
	}
	return FALSE;
}

#define HIMETRIC_INCH   2540    // HIMETRIC units per inch

void HIMETRICtoDP( HDC hDC, LONG * plX, LONG * plY )
{
	int nMapMode;
	if ( ( nMapMode = GetMapMode(hDC) ) < MM_ISOTROPIC && nMapMode != MM_TEXT )
	{
		// when using a constrained map mode, map against physical inch
		SetMapMode( hDC, MM_HIMETRIC );
		POINT pt = { *plX, *plY };
		LPtoDP( hDC, &pt, 1 );
		SetMapMode( hDC, nMapMode );
		*plX = pt.x;
		*plY = pt.y;
	}
	else
	{
		// map against logical inch for non-constrained mapping modes
		int cxPerInch, cyPerInch;
		cxPerInch = GetDeviceCaps( hDC, LOGPIXELSX );
		cyPerInch = GetDeviceCaps( hDC, LOGPIXELSY );
		*plX = MulDiv( *plX, cxPerInch, HIMETRIC_INCH);
		*plY = MulDiv( *plY, cyPerInch, HIMETRIC_INCH);
	}
}

void HIMETRICtoDP( HDC hDC, LPPOINT lpPoint )
{
	int nMapMode;
	if ( ( nMapMode = GetMapMode(hDC) ) < MM_ISOTROPIC && nMapMode != MM_TEXT )
	{
		// when using a constrained map mode, map against physical inch
		SetMapMode( hDC, MM_HIMETRIC );
		LPtoDP( hDC, lpPoint, 1 );
		SetMapMode( hDC, nMapMode );
	}
	else
	{
		// map against logical inch for non-constrained mapping modes
		int cxPerInch, cyPerInch;
		cxPerInch = GetDeviceCaps( hDC, LOGPIXELSX );
		cyPerInch = GetDeviceCaps( hDC, LOGPIXELSY );
		lpPoint->x = MulDiv(lpPoint->x, cxPerInch, HIMETRIC_INCH);
		lpPoint->y = MulDiv(lpPoint->y, cyPerInch, HIMETRIC_INCH);
	}
}

void DPtoHIMETRIC( HDC hDC, LONG * plX, LONG * plY )
{
	int nMapMode;
	if ( ( nMapMode = GetMapMode(hDC) ) < MM_ISOTROPIC && nMapMode != MM_TEXT )
	{
		// when using a constrained map mode, map against physical inch
		SetMapMode( hDC, MM_HIMETRIC );
		POINT pt = { *plX, *plY };
		DPtoLP( hDC, &pt, 1 );
		SetMapMode( hDC, nMapMode );
		*plX = pt.x;
		*plY = pt.y;
	}
	else
	{
		// map against logical inch for non-constrained mapping modes
		int cxPerInch, cyPerInch;
		cxPerInch = GetDeviceCaps( hDC, LOGPIXELSX );
		cyPerInch = GetDeviceCaps( hDC, LOGPIXELSY );
		*plX = MulDiv( *plX, HIMETRIC_INCH, cxPerInch );
		*plY = MulDiv( *plY, HIMETRIC_INCH, cyPerInch );
	}
}

void DPtoHIMETRIC( HDC hDC, LPPOINT lpPoint )
{
	int nMapMode;
	if ( ( nMapMode = GetMapMode(hDC) ) < MM_ISOTROPIC && nMapMode != MM_TEXT )
	{
		// when using a constrained map mode, map against physical inch
		SetMapMode( hDC, MM_HIMETRIC );
		DPtoLP( hDC, lpPoint, 1 );
		SetMapMode( hDC, nMapMode );
	}
	else
	{
		// map against logical inch for non-constrained mapping modes
		int cxPerInch, cyPerInch;
		cxPerInch = GetDeviceCaps( hDC, LOGPIXELSX );
		cyPerInch = GetDeviceCaps( hDC, LOGPIXELSY );
		lpPoint->x = MulDiv( lpPoint->x, HIMETRIC_INCH, cxPerInch );
		lpPoint->y = MulDiv( lpPoint->y, HIMETRIC_INCH, cyPerInch );
	}
}

// 坐标转换系列函数 -------------------------------------------------------


// GDI+ -------------------------------------------------------------------
GdiplusInit::GdiplusInit()
{
	// Initialize GDI+.
	Gdiplus::GdiplusStartup( &_gdiplusToken, &_gdiplusStartupInput, NULL);
}

GdiplusInit::~GdiplusInit()
{
	Gdiplus::GdiplusShutdown(_gdiplusToken);
}

int GetImageEncoderFromMIME( LPCTSTR lpszMimeType, CLSID * pEncoderClsid )
{
	using namespace Gdiplus;
	UINT num = 0;          // number of image encoders
	UINT size = 0;         // size of the image encoder array in bytes
	ImageCodecInfo * pImageCodecInfo = NULL;
	GetImageEncodersSize( &num, &size );
	if ( size == 0 ) return -1;  // Failure
	pImageCodecInfo = (ImageCodecInfo *)malloc(size);
	if ( pImageCodecInfo == NULL ) return -1;  // Failure
	GetImageEncoders( num, size, pImageCodecInfo );
	UINT i;
	for( i = 0; i < num; ++i )
	{
		ImageCodecInfo & info = pImageCodecInfo[i];
		String strMimeType = UnicodeToString( info.MimeType ? info.MimeType : L"" );
		if ( strMimeType == lpszMimeType )
		{
			*pEncoderClsid = info.Clsid;
			break;
		}
	}
	free(pImageCodecInfo);
	if ( i < num )
	{
		return i; // Success
	}
	return -1;  // Failure
}

int GetImageEncoderFromExtName( LPCTSTR lpszExtName, CLSID * pEncoderClsid )
{
	using namespace Gdiplus;
	UINT num = 0;          // number of image encoders
	UINT size = 0;         // size of the image encoder array in bytes
	ImageCodecInfo * pImageCodecInfo = NULL;
	GetImageEncodersSize( &num, &size );
	if ( size == 0 ) return -1;  // Failure
	pImageCodecInfo = (ImageCodecInfo *)malloc(size);
	if ( pImageCodecInfo == NULL ) return -1;  // Failure
	GetImageEncoders( num, size, pImageCodecInfo );
	UINT i;
	String strExtName = lpszExtName;
	for( i = 0; i < num; ++i )
	{
		ImageCodecInfo & info = pImageCodecInfo[i];
		String strFilenameExtension = UnicodeToString( info.FilenameExtension ? info.FilenameExtension : L"" );
		StringArray arrExtName;
		int nExtNameCount = StrSplit( strFilenameExtension.c_str(), TEXT(";"), &arrExtName );
		int j;
		for ( j = 0; j < nExtNameCount; ++j )
		{
			//arrExtName[j] = arrExtName[j].substr(2); // *.xxx skip 2 chars
			_tcslwr(&arrExtName[j][0]);
			_tcslwr(&strExtName[0]);
			if ( arrExtName[j].find(strExtName) != String::npos )
			{
				break;
			}
		}
		if ( j < nExtNameCount )
		{
			*pEncoderClsid = info.Clsid;
			break;
		}
	}
	free(pImageCodecInfo);
	if ( i < num )
	{
		return i; // Success
	}
	return -1;  // Failure
}


// IStream 相关 -----------------------------------------------------------
IStream * CreateStreamExistingFile( LPCTSTR lpszFileName )
{
	IStream * pStream = NULL;
	HRESULT hr;
	HANDLE hFile = CreateFile(
		lpszFileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if ( INVALID_HANDLE_VALUE == hFile )
	{
		return NULL;
	}
	DWORD dwFileSize, dw;
	dwFileSize = GetFileSize( hFile, &dw ); // 获得文件大小
	HGLOBAL hGlobal = GlobalAlloc( GMEM_MOVEABLE, dwFileSize );
	if ( hGlobal == NULL )
	{
		CloseHandle(hFile);
		return NULL;
	}

	LPVOID pBuffer = GlobalLock(hGlobal);
	ReadFile( hFile, pBuffer, dwFileSize, &dw, NULL );
	GlobalUnlock(hGlobal);

	CloseHandle(hFile); // 内容已拷贝到内存,再无需File

	hr = CreateStreamOnHGlobal( hGlobal, TRUE, &pStream ); // 创建 IStream
	if ( FAILED(hr) )
	{
		GlobalFree(hGlobal);
		return NULL;
	}

	return pStream;
}

IStream * CreateStreamFromBuffer( LPCVOID lpBuffer, DWORD dwSize )
{
	HRESULT hr;
	IStream * pStream = NULL;
	HGLOBAL hGlobal = GlobalAlloc( GMEM_MOVEABLE, dwSize );
	if ( hGlobal == NULL )
	{
		return NULL;
	}

	LPVOID lpData = GlobalLock(hGlobal);
	CopyMemory( lpData, lpBuffer, dwSize );
	GlobalUnlock(hGlobal);

	hr = CreateStreamOnHGlobal( hGlobal, TRUE, &pStream ); // 创建 IStream
	if ( FAILED(hr) )
	{
		GlobalFree(hGlobal);
		return NULL;
	}
	return pStream;
}

IStream * CreateStreamFromResourceEx( HMODULE hModule, UINT uResourceID, LPCTSTR lpType )
{
	IStream * pStream = NULL;
	HRSRC hRSRC = FindResource( hModule, MAKEINTRESOURCE(uResourceID), lpType);
	if ( hRSRC != NULL )
	{
		DWORD dwSize = SizeofResource( hModule, hRSRC );
		HGLOBAL hRes = LoadResource( hModule, hRSRC );
		LPVOID lpData = LockResource(hRes);
		pStream = CreateStreamFromBuffer( lpData, dwSize );

		FreeResource(hRes);
	}

	return pStream;
}

IStream * CreateStreamFromResource( UINT uResourceID, LPCTSTR lpType )
{
	return CreateStreamFromResourceEx( GetModuleHandle(NULL), uResourceID, lpType );
}

// 外壳(Shell)相关 --------------------------------------------------------

class SimpleFileSysBindData : public IFileSystemBindData
{ 
public:
	SimpleFileSysBindData() : _cRef(1)
	{
		ZeroMemory( &_fd, sizeof(_fd) );
	}
	// *** IUnknown methods ***
	STDMETHODIMP QueryInterface( REFIID riid, void * * ppvObj )
	{
		if ( riid == IID_IFileSystemBindData )
		{
			*ppvObj = static_cast<IFileSystemBindData *>(this);
			AddRef();
			return S_OK;
		}
		else if ( riid == IID_IUnknown )
		{
			*ppvObj = static_cast<IUnknown *>(this);
			AddRef();
			return S_OK;
		}
		return E_NOINTERFACE;
	}
	STDMETHODIMP_(ULONG) AddRef(void)
	{
		return InterlockedIncrement(&_cRef);
	}
	STDMETHODIMP_(ULONG) Release(void)
	{
		LONG cRef = InterlockedDecrement(&_cRef);
		if ( !cRef )
			delete this;
		return cRef;
	}
	
	// *** IFileSystemBindData Methods ***
	STDMETHODIMP SetFindData( WIN32_FIND_DATAW const * pfd )
	{
		_fd = *pfd;
		return S_OK;
	}
	STDMETHODIMP GetFindData( WIN32_FIND_DATAW * pfd )
	{
		*pfd = _fd;
		return S_OK;
	}
private:
	~SimpleFileSysBindData()
	{
	}
	
	LONG _cRef;
	WIN32_FIND_DATAW _fd;
};

HRESULT GetSimpleIDListFromPath( LPWSTR pwszPath, WIN32_FIND_DATAW * pfd, LPITEMIDLIST * ppidl )
{
	HRESULT hr;
	IUnknown * pI;
	IFileSystemBindData * pfsbd;
	pI = static_cast<IFileSystemBindData *>(new SimpleFileSysBindData);
	hr = pI->QueryInterface( IID_IFileSystemBindData, (void * *)&pfsbd );
	pI->Release();

	if ( FAILED(hr) )
		return hr;

	if ( pfd )
		pfsbd->SetFindData(pfd);

	LPBINDCTX pBindCtx;
	hr = CreateBindCtx( 0, &pBindCtx );
	if ( FAILED(hr) )
	{
		pfsbd->Release();
		return hr;
	}
	pBindCtx->RegisterObjectParam( STR_FILE_SYS_BIND_DATA, pfsbd );
	pfsbd->Release();

	// 得到桌面的目录
	LPSHELLFOLDER pFolder;
	hr = SHGetDesktopFolder(&pFolder);
	if ( FAILED(hr) )
	{
		pBindCtx->Release();
		return hr;
	}
	hr = pFolder->ParseDisplayName( NULL, pBindCtx, (LPOLESTR)pwszPath, NULL, ppidl, NULL );
	pFolder->Release();
	pBindCtx->Release();

	return hr;
}

LPITEMIDLIST GetItemIDListFromFilePath( String const & strFilePath )
{
	if ( strFilePath.empty() )
	{
		return NULL;
	}

	HRESULT hr;
	// 得到桌面的目录
	LPSHELLFOLDER pDesktopFolder = NULL;
	hr = SHGetDesktopFolder(&pDesktopFolder);
	if ( FAILED(hr) )
	{
		return NULL;
	}

	UnicodeString olestr = StringToUnicode(strFilePath);
	// 得到文件路径对应的ItemIDList
	LPITEMIDLIST pItemIDList = NULL;
	hr = pDesktopFolder->ParseDisplayName( NULL, NULL, (LPOLESTR)&olestr[0], NULL, &pItemIDList, NULL );
	pDesktopFolder->Release();
	if ( FAILED(hr) )
	{
		return NULL;
	}
	return pItemIDList;
}

LPITEMIDLIST GetSimpleIDListFromPath( String const & strFilePath )
{
	LPITEMIDLIST pItemIDList = NULL;
	HRESULT hr = GetSimpleIDListFromPath( (LPWSTR)StringToUnicode(strFilePath).c_str(), NULL, &pItemIDList );
	return pItemIDList;
}
