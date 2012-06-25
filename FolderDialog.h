// FolderDialog.h: interface for the FolderDialog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BROWSEFORFOLDER_H__0AA4D448_7E82_409B_885E_FB788431AC98__INCLUDED_)
#define AFX_BROWSEFORFOLDER_H__0AA4D448_7E82_409B_885E_FB788431AC98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class FolderDialog
{
	BROWSEINFO _bi;
	String _strPath;
	String _strDisplay;
	String _strDlgText;
public:
	FolderDialog( HWND hWndOwner, LPCTSTR lpszDlgText = NULL );
	BOOL DoBrowse( LPCTSTR lpszRootDir = NULL );	// 显示对话框
	String GetDisplay() const;	// 选择的文件夹
	String GetPath() const;	// 选择的路径
};


#endif // !defined(AFX_BROWSEFORFOLDER_H__0AA4D448_7E82_409B_885E_FB788431AC98__INCLUDED_)
