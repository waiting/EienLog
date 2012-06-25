#if !defined(AFX_SETTINGSDLG_H__FD77A3AD_F30A_425B_9A18_FCD672202710__INCLUDED_)
#define AFX_SETTINGSDLG_H__FD77A3AD_F30A_425B_9A18_FCD672202710__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingsDlg.h : header file
//
#include <comdef.h>
/////////////////////////////////////////////////////////////////////////////
// CSettingsDlg dialog

class CSettingsDlg : public CDialog
{
// Construction
public:
	CSettingsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingsDlg)
	enum { IDD = IDD_SETTINGS_DIALOG };
	BOOL	_bSaveLogFiles;
	BOOL	_bShowDetail;
	int		_nCacheCount;
	int		_nLogLength;
	CString	_strSavePath;
	CString	_strShareName;
	int		_nShowCount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:
	IStreamPtr _pLogSmallImgStream;
	std::auto_ptr<Gdiplus::Image> _pImage;
	// Generated message map functions
	//{{AFX_MSG(CSettingsDlg)
	afx_msg void OnPaint();
	afx_msg void OnButtonBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGSDLG_H__FD77A3AD_F30A_425B_9A18_FCD672202710__INCLUDED_)
