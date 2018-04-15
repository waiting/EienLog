#if !defined(AFX_DETAILLOGDLG_H__3BF1D00D_FB87_47B1_8FA3_AFBBF06E5C98__INCLUDED_)
#define AFX_DETAILLOGDLG_H__3BF1D00D_FB87_47B1_8FA3_AFBBF06E5C98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DetailLogDlg.h : header file
//
#include "MFC/ModelessDialog.h"
/////////////////////////////////////////////////////////////////////////////
// CDetailLogDlg dialog

class CDetailLogDlg : public ModelessDialog
{
    // Construction
public:
    //CDetailLogDlg(CWnd* pParent = NULL);   // standard constructor
    CDetailLogDlg();
    // Dialog Data
    //{{AFX_DATA(CDetailLogDlg)
    enum { IDD = IDD_DETAILLOG_DIALOG };
    // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA

    void SetLog( String const & strLog );
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDetailLogDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    //}}AFX_VIRTUAL

    // Implementation
protected:
    CRichEditCtrl _RichEdit;
    // Generated message map functions
    //{{AFX_MSG(CDetailLogDlg)
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DETAILLOGDLG_H__3BF1D00D_FB87_47B1_8FA3_AFBBF06E5C98__INCLUDED_)
