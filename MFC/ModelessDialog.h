// ModelessDialog.h: interface for the ModelessDialog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODELESSDIALOG_H__29E0B039_CEB5_418A_8684_854E5E240C92__INCLUDED_)
#define AFX_MODELESSDIALOG_H__29E0B039_CEB5_418A_8684_854E5E240C92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ModelessDialog : public CDialog  
{
public:
	ModelessDialog();
	virtual ~ModelessDialog();
	// Attributes
public:
	void AutoDelete( BOOL bAutoDel ) { _bAutoDelete = bAutoDel; } // 自动删除对象,当new分配时又不想管理内存,请设置其为TRUE
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ModelessDialog)
protected:
	virtual void PostNcDestroy();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_VIRTUAL
	
	// Implementation
	
	// Generated message map functions
protected:
	BOOL _bAutoDelete;
	//{{AFX_MSG(ModelessDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};




#endif // !defined(AFX_MODELESSDIALOG_H__29E0B039_CEB5_418A_8684_854E5E240C92__INCLUDED_)
