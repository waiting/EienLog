// ModelessDialog.cpp: implementation of the ModelessDialog class.
//
//////////////////////////////////////////////////////////////////////
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include <afxcmn.h>

#include "ModelessDialog.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ModelessDialog::ModelessDialog() : _bAutoDelete(TRUE)
{
	
}

ModelessDialog::~ModelessDialog()
{
}

void ModelessDialog::PostNcDestroy()
{
	if ( _bAutoDelete )
	{
		delete this;
	}
}

void ModelessDialog::OnOK()
{
	CDialog::OnOK();
	_bAutoDelete && DestroyWindow();
}

void ModelessDialog::OnCancel()
{
	CDialog::OnCancel();
	_bAutoDelete && DestroyWindow();
}

BEGIN_MESSAGE_MAP(ModelessDialog, CDialog)
	//{{AFX_MSG_MAP(ModelessDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


