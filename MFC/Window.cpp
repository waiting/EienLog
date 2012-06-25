// Window.cpp : implementation file
//

#include "ImageMerge.h"
#include "Window.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Window

Window::Window() : _bAutoDelete(FALSE)
{
}

Window::~Window()
{
}


BEGIN_MESSAGE_MAP(Window, CWnd)
	//{{AFX_MSG_MAP(Window)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void Window::PostNcDestroy()
{
	if ( _bAutoDelete )
	{
		delete this;
	}
}

/////////////////////////////////////////////////////////////////////////////
// Window message handlers
