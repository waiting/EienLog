// FolderDialog.cpp: implementation of the FolderDialog class.
//
//////////////////////////////////////////////////////////////////////
#include "utils.h"
#include "FolderDialog.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FolderDialog::FolderDialog( HWND hWndOwner, LPCTSTR lpszDlgText /*= NULL */ )
{
	ZeroMemory( &_bi, sizeof(_bi) );
	_strPath.resize(MAX_PATH);
	_strDisplay.resize(MAX_PATH);

	_bi.pszDisplayName = &_strDisplay[0];
	_bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI | BIF_STATUSTEXT | BIF_UAHINT;

	_bi.hwndOwner = hWndOwner;
	if ( lpszDlgText != NULL )
		_strDlgText = lpszDlgText;
	else
		_strDlgText = TEXT("Ñ¡ÔñÎÄ¼þ¼Ð");
}

BOOL FolderDialog::DoBrowse( LPCTSTR lpszRootDir )
{
	LPMALLOC pMalloc;
	LPITEMIDLIST pItemIDList;
	HRESULT hr;
	BOOL bRet = FALSE;

	_bi.lpszTitle = _strDlgText.c_str();

	if ( lpszRootDir != NULL && *lpszRootDir )
		_bi.pidlRoot = GetItemIDListFromFilePath(lpszRootDir);
	else
		_bi.pidlRoot = NULL;

	pItemIDList = SHBrowseForFolder(&_bi);

	hr = SHGetMalloc(&pMalloc);

	if ( pItemIDList != NULL )
	{
		SHGetPathFromIDList( pItemIDList, &_strPath[0] );
		if ( pMalloc != NULL )
			pMalloc->Free(pItemIDList);

		bRet = TRUE;
	}

	if ( pMalloc != NULL && _bi.pidlRoot != NULL )
	{
		pMalloc->Free( (void *)_bi.pidlRoot );
		_bi.pidlRoot = NULL;
	}

	if ( pMalloc != NULL )
		pMalloc->Release();

	return bRet;
}

String FolderDialog::GetPath() const
{
	return _strPath.c_str();
}

String FolderDialog::GetDisplay() const
{
	return _strDisplay.c_str();
}
