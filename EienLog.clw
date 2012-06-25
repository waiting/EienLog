; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=LogListBox
LastTemplate=CListBox
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "EienLog.h"

ClassCount=6
Class1=CEienLogApp
Class2=CEienLogDlg

ResourceCount=4
Resource2=IDD_SETTINGS_DIALOG
Resource3=IDD_EIENLOG_DIALOG
Resource1=IDR_MAINFRAME
Class3=CSettingsDlg
Class4=CDetailLogDlg
Class5=RichEditCtrl
Class6=LogListBox
Resource4=IDD_DETAILLOG_DIALOG

[CLS:CEienLogApp]
Type=0
HeaderFile=EienLog.h
ImplementationFile=EienLog.cpp
Filter=N

[CLS:CEienLogDlg]
Type=0
HeaderFile=EienLogDlg.h
ImplementationFile=EienLogDlg.cpp
Filter=D
LastObject=CEienLogDlg
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_EIENLOG_DIALOG]
Type=1
Class=CEienLogDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON_SETTINGS,button,1342242816

[DLG:IDD_SETTINGS_DIALOG]
Type=1
Class=CSettingsDlg
ControlCount=15
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_SHOW_COUNT,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_CACHE_COUNT,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_SAVE_PATH,edit,1350631552
Control7=IDC_BUTTON_BROWSE,button,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_SHARE_NAME,edit,1350631552
Control10=IDC_CHECK_SAVE,button,1342242819
Control11=IDC_CHECK_SHOWDETAIL,button,1342242819
Control12=IDC_STATIC,static,1342308352
Control13=IDC_EDIT_LOG_LENGTH,edit,1350631552
Control14=IDOK,button,1342242817
Control15=IDCANCEL,button,1342242816

[DLG:IDD_DETAILLOG_DIALOG]
Type=1
Class=CDetailLogDlg
ControlCount=0

[CLS:CSettingsDlg]
Type=0
HeaderFile=SettingsDlg.h
ImplementationFile=SettingsDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSettingsDlg
VirtualFilter=dWC

[CLS:CDetailLogDlg]
Type=0
HeaderFile=DetailLogDlg.h
ImplementationFile=DetailLogDlg.cpp
BaseClass=ModelessDialog
Filter=D
LastObject=CDetailLogDlg
VirtualFilter=dWC

[CLS:RichEditCtrl]
Type=0
HeaderFile=RichEditCtrl.h
ImplementationFile=RichEditCtrl.cpp
BaseClass=CRichEditCtrl
Filter=W
VirtualFilter=WC
LastObject=RichEditCtrl

[CLS:LogListBox]
Type=0
HeaderFile=LogListBox.h
ImplementationFile=LogListBox.cpp
BaseClass=CListBox
Filter=W
VirtualFilter=bWC
LastObject=LogListBox

