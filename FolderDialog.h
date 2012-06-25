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
	BOOL DoBrowse( LPCTSTR lpszRootDir = NULL );	// ��ʾ�Ի���
	String GetDisplay() const;	// ѡ����ļ���
	String GetPath() const;	// ѡ���·��
};


#endif // !defined(AFX_BROWSEFORFOLDER_H__0AA4D448_7E82_409B_885E_FB788431AC98__INCLUDED_)
