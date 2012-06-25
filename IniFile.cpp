// IniFile.cpp: implementation of the IniFile class.
//
//////////////////////////////////////////////////////////////////////

#include "utils.h"
#include "IniFile.h"
#include <tchar.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IniFile::IniFile( LPCTSTR szIniFile, BOOL bInWindowsDir ) : _strIniFile(szIniFile)
{
	int nLen;
	nLen = _strIniFile.length();
	/* 不是全路径,eg C:\ */
	if ( !( nLen > 1 && _strIniFile[1] == _T(':') ) )
	{
		// 不想在windows目录
		if ( !bInWindowsDir )
		{
			if ( nLen > 1 )
			{
				if ( !( _strIniFile[0] == _T('.') && _strIniFile[1] == _T('\\') ) )
				{
					_strIniFile = _T(".\\") + _strIniFile;
				}
			}
			else
				_strIniFile = _T(".\\") + _strIniFile;
		}
	}
}

BOOL IniFile::SetSection( LPCTSTR szSection, LPCTSTR lpKeyVal )
{
	return WritePrivateProfileSection( szSection, lpKeyVal, _strIniFile.c_str() );
}

BOOL IniFile::SetValue(LPCTSTR szSection, LPCTSTR szKeyName, LPCTSTR szValue)
{
	return WritePrivateProfileString( szSection, szKeyName, szValue, _strIniFile.c_str() );
}

BOOL IniFile::SetValue( LPCTSTR szSection, LPCTSTR szKeyName, INT nValue, BOOL bSigned /*= TRUE*/ )
{
	return SetValue( szSection, szKeyName, Format( bSigned ? _T("%d") : _T("%u"), nValue ).c_str() );
}

BOOL IniFile::SetValue( LPCTSTR szSection, LPCTSTR szKeyName, DOUBLE dblValue )
{
	return SetValue( szSection, szKeyName, Format( _T("%lf"), dblValue ).c_str() );
}

BOOL IniFile::SetData( LPCTSTR szSection, LPCTSTR szKeyName, LPCVOID lpDataBuf, UINT uSizeData )
{
	return WritePrivateProfileStruct( szSection, szKeyName, (LPVOID)lpDataBuf, uSizeData, _strIniFile.c_str() );
}

INT IniFile::GetValue( LPCTSTR szSection, LPCTSTR szKeyName, INT nDefault )
{
	return (INT)GetPrivateProfileInt( szSection, szKeyName, nDefault, _strIniFile.c_str() );
}

String IniFile::GetValue( LPCTSTR szSection, LPCTSTR szKeyName, LPCTSTR szDefault )
{
	DWORD nBufferSize = 256;
	DWORD dwCopied = 0, dwTmp = 0;
	String szBuffer;
	do 
	{
		nBufferSize <<= 1;
		szBuffer.resize(nBufferSize);
		dwCopied = GetPrivateProfileString( szSection, szKeyName, szDefault, &szBuffer[0], nBufferSize, _strIniFile.c_str() );
		if ( szSection && szKeyName )
			dwTmp = 1;
		else
			dwTmp = 2;
	}
	while ( nBufferSize - dwTmp == dwCopied );
	return szBuffer.c_str();
}

DOUBLE IniFile::GetValue( LPCTSTR szSection, LPCTSTR szKeyName, DOUBLE dblDefault )
{
	DOUBLE dblValue;
	String szDefault = Format( _T("%lf"), dblDefault );
	String szValue = GetValue( szSection, szKeyName, szDefault.c_str() );
	LPTSTR pszEnd;
	dblValue = _tcstod( szValue.c_str(), &pszEnd );
	return dblValue;
}

INT IniFile::GetSection( LPCTSTR szSection, StringArray * pArr )
{
	DWORD nBufferSize = 512;
	DWORD dwCopied = 0;
	String szBuffer;
	do 
	{
		nBufferSize <<= 1;
		szBuffer.resize(nBufferSize);
		dwCopied = GetPrivateProfileSection( szSection, &szBuffer[0], nBufferSize, _strIniFile.c_str() );
	}
	while ( nBufferSize - 2 == dwCopied );

	LPCTSTR lpsz = (LPCTSTR)szBuffer.c_str();
	INT nSubLen = 0;
	pArr->clear();
	while ( ( nSubLen = lstrlen(lpsz) ) > 0 )
	{
		pArr->push_back(lpsz);
		lpsz += nSubLen + 1;
	}
	return pArr->size();
}

BOOL IniFile::GetData( LPCTSTR szSection, LPCTSTR szKeyName, LPVOID lpDataBuf, UINT uSizeData )
{
	return GetPrivateProfileStruct( szSection, szKeyName, lpDataBuf, uSizeData, _strIniFile.c_str() );
}

INT IniFile::SectionNames( StringArray * pSectionNames )
{
	DWORD nBufferSize = 512;
	DWORD dwCopied = 0;
	String szBuffer;
	do
	{
		nBufferSize <<= 1;
		szBuffer.resize(nBufferSize);
		dwCopied = GetPrivateProfileSectionNames( &szBuffer[0], nBufferSize, _strIniFile.c_str() );
	}
	while (nBufferSize - 2 == dwCopied);
	
	LPCTSTR lpsz = (LPCTSTR)szBuffer.c_str();
	INT nSubLen = 0;
	pSectionNames->clear();
	while ( ( nSubLen = lstrlen(lpsz) ) > 0 )
	{
		pSectionNames->push_back(lpsz);
		lpsz += nSubLen + 1;
	}
	return pSectionNames->size();
}
