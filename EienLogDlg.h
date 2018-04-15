
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
    // 配置数据
    struct SettingsData
    {
        BOOL bSaveLogFiles; // 是否保存日志文件
        BOOL bShowDetail; // 是否显示日志详细框
        int nCacheCount; // 缓存的日志条数
        int nLogLength; // 单条日志长度
        int nShowCount; // 日志显示条数
        String strSavePath; // 保存路径
        String strShareName; // 共享名称
    } _settings;
    // 命令行获取共享名
    BOOL _bShareNameFromCMD;
    // Dialog Data
    //{{AFX_DATA(CEienLogDlg)
    enum { IDD = IDD_EIENLOG_DIALOG };
    //}}AFX_DATA
    LogListBox _LogListBox;

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

    // 共享的对象
    HANDLE _hShareMem;
    HANDLE _hMutex;

    // 详细日志对话框
    CDetailLogDlg _DetailLogDlg;

    // 日志缓冲
    StringArray _LogsCache;
    StringArray _LogsShow;

    void CreateShareData();
    void FreeShareData();

    EienLog::ShareData * LockShareMem();
    void UnlockShareMem( EienLog::ShareData * lpData );
    // 更新UI, 隐藏/显示详细日志窗口
    void UpdateUI();
    // 保存日志
    void SaveLogFiles();
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    // Generated message map functions
    //{{AFX_MSG(CEienLogDlg)
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
