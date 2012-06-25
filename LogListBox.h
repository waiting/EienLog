#if !defined(AFX_LOGLISTBOX_H__97A53116_6CA6_4916_84FC_185339794B8F__INCLUDED_)
#define AFX_LOGLISTBOX_H__97A53116_6CA6_4916_84FC_185339794B8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogListBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LogListBox window

class LogListBox : public CListBox
{
// Construction
public:
	LogListBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LogListBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~LogListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(LogListBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGLISTBOX_H__97A53116_6CA6_4916_84FC_185339794B8F__INCLUDED_)
