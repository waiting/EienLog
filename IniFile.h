// IniFile.h: interface for the IniFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILE_H__E8D871D7_586C_493D_8028_BD6763A02D2D__INCLUDED_)
#define AFX_INIFILE_H__E8D871D7_586C_493D_8028_BD6763A02D2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/*
	WritePrivateProfileSection
	WritePrivateProfileString
	WritePrivateProfileStruct
	GetPrivateProfileInt
	GetPrivateProfileSection
	GetPrivateProfileSectionNames
	GetPrivateProfileString
	GetPrivateProfileStruct
 */

class IniFile
{
	String _strIniFile;
	//StringArray _sections;
public:
	IniFile( LPCTSTR szIniFile, BOOL bInWindowsDir = FALSE );
public:

	BOOL SetSection( LPCTSTR szSection, LPCTSTR lpKeyVal );
	BOOL SetValue( LPCTSTR szSection, LPCTSTR szKeyName, LPCTSTR szValue );
	BOOL SetValue( LPCTSTR szSection, LPCTSTR szKeyName, INT nValue, BOOL bSigned = TRUE );
	BOOL SetValue( LPCTSTR szSection, LPCTSTR szKeyName, DOUBLE dblValue );
	BOOL SetData( LPCTSTR szSection, LPCTSTR szKeyName, LPCVOID lpDataBuf, UINT uSizeData );

	INT GetValue( LPCTSTR szSection, LPCTSTR szKeyName, INT nDefault );
	String GetValue( LPCTSTR szSection, LPCTSTR szKeyName, LPCTSTR szDefault );
	DOUBLE GetValue( LPCTSTR szSection, LPCTSTR szKeyName, DOUBLE dblDefault );
	INT GetSection( LPCTSTR szSection, StringArray * pArr );
	BOOL GetData( LPCTSTR szSection, LPCTSTR szKeyName, LPVOID lpDataBuf, UINT uSizeData );
	INT SectionNames( StringArray * pSectionNames );
};

#endif // !defined(AFX_INIFILE_H__E8D871D7_586C_493D_8028_BD6763A02D2D__INCLUDED_)
