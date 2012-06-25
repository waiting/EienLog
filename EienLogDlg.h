
#if !defined(AFX_EIENLOGDLG_H__1A6EB49A_F340_4D20_9DD5_D7E4934AF563__INCLUDED_)
#define AFX_EIENLOGDLG_H__1A6EB49A_F340_4D20_9DD5_D7E4934AF563__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DetailLogDlg.h"
#include "LogListBox.h"
/////////////////////////////////////////////////////////////////////////////
// CEienLogDlg dialog

class CEienLogDlg : public CDialog
{
// Construction
public:
	CEienLogDlg(CWnd* pParent = NULL);	// standard constructor
	~CEienLogDlg();
	// ��������
	struct SettingsData
	{
		BOOL bSaveLogFiles; // �Ƿ񱣴���־�ļ�
		BOOL bShowDetail; // �Ƿ���ʾ��־��ϸ��
		int nCacheCount; // �������־����
		int nLogLength; // ������־����
		int nShowCount; // ��־��ʾ����
		String strSavePath; // ����·��
		String strShareName; // ��������
	} _settings;
	// �����л�ȡ������
	BOOL _bShareNameFromCMD;
// Dialog Data
	//{{AFX_DATA(CEienLogDlg)
	enum { IDD = IDD_EIENLOG_DIALOG };
	//}}AFX_DATA
	LogListBox	_LogListBox;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEienLogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	IniFile _IniFile;
	String _strIniFileSection;

	// ����Ķ���
	HANDLE _hShareMem;
	HANDLE _hMutex;

	// ��ϸ��־�Ի���
	CDetailLogDlg _DetailLogDlg;

	// ��־����
	StringArray _LogsCache;
	StringArray _LogsShow;

	void CreateShareData();
	void FreeShareData();

	EienLog::ShareData * LockShareMem();
	void UnlockShareMem( EienLog::ShareData * lpData );
	// ����UI, ����/��ʾ��ϸ��־����
	void UpdateUI();
	// ������־
	void SaveLogFiles();
	// Generated message map functions
	//{{AFX_MSG(CEienLogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonSettings();
	afx_msg LRESULT OnLogNotify( WPARAM wParam, LPARAM lParam );
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSelChangeListLogs();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EIENLOGDLG_H__1A6EB49A_F340_4D20_9DD5_D7E4934AF563__INCLUDED_)
