; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgProAdi
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "LisACa.h"
LastPage=0

ClassCount=10
Class1=CLisACaApp
Class2=CLisACaDoc
Class3=CLisACaView
Class4=CMainFrame

ResourceCount=10
Resource1=IDD_ABOUTBOX
Resource2=IDD_DLGLISACF (Spanish (Mexican))
Class5=CAboutDlg
Resource3=IDD_DLGCONAUL (Spanish (Mexican))
Resource4=IDD_ABOUTBOX (Spanish (Modern))
Resource5=IDD_DLGPROADI (Spanish (Mexican))
Class6=CDlgLisACa
Resource6=IDD_DLGLISACA (Spanish (Mexican))
Class7=CDlgLisACF
Resource7=IDD_LISACA_FORM (Spanish (Modern))
Class8=CDlgConAul
Resource8=IDR_MAINFRAME (English (U.S.))
Class9=CDlgPobIni
Resource9=IDD_DLGPOBINI (Spanish (Mexican))
Class10=CDlgProAdi
Resource10=IDR_MAINFRAME (Spanish (Modern))

[CLS:CLisACaApp]
Type=0
HeaderFile=LisACa.h
ImplementationFile=LisACa.cpp
Filter=N

[CLS:CLisACaDoc]
Type=0
HeaderFile=LisACaDoc.h
ImplementationFile=LisACaDoc.cpp
Filter=N
LastObject=CLisACaDoc

[CLS:CLisACaView]
Type=0
HeaderFile=LisACaView.h
ImplementationFile=LisACaView.cpp
Filter=D
BaseClass=CFormView
VirtualFilter=VWC
LastObject=ID_PRO_CPANUA


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=LisACa.cpp
ImplementationFile=LisACa.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command17=ID_NEXT_PANE
Command18=ID_PREV_PANE
CommandCount=21

[DLG:IDD_LISACA_FORM (Spanish (Modern))]
Type=1
Class=?
ControlCount=15
Control1=IDC_LISDOC,combobox,1344340225
Control2=IDC_STATIC,static,1342308352
Control3=IDC_TOTCDO,edit,1342244992
Control4=IDC_STATIC,static,1342308352
Control5=IDC_TIPNOT,edit,1342244992
Control6=IDC_TIPEVA,edit,1342244992
Control7=IDC_LISAUL,combobox,1344339969
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_LISCDO,listbox,1352728833
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_LISHOR,listbox,1352728833
Control15=IDC_LISCHO,listbox,1352728833

[ACL:IDR_MAINFRAME (Spanish (Modern))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_ABOUTBOX (Spanish (Modern))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308352

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_PRINT_PREVIEW
Command2=ID_FILE_PRINT
Command3=ID_PRO_ASIHOR
Command4=ID_PRO_CPANUA
Command5=ID_PRO_CONCIL
Command6=ID_PRO_CONAUL
Command7=ID_PRO_CONHOR
Command8=ID_PRO_CONPIN
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_PRINT
Command2=ID_FILE_PRINT_PREVIEW
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_DLGLISACA (Spanish (Mexican))]
Type=1
Class=CDlgLisACa
ControlCount=6
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_LISHOR,listbox,1352728833
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:CDlgLisACa]
Type=0
HeaderFile=lisacaview.h
ImplementationFile=lisacaview.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgLisACa
VirtualFilter=dWC

[DLG:IDD_DLGLISACF (Spanish (Mexican))]
Type=1
Class=CDlgLisACF
ControlCount=32
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_TEXUNO,static,1342308352
Control11=IDC_TEXDOS,static,1342308352
Control12=IDC_TEXTRE,static,1342308352
Control13=IDC_TEXCUA,static,1342308352
Control14=IDC_TEXCIN,static,1342308352
Control15=IDC_EDIUNO,edit,1350631552
Control16=IDC_EDIDOS,edit,1350631552
Control17=IDC_EDICIN,edit,1350631552
Control18=IDC_EDICUA,edit,1350631552
Control19=IDC_EDITRE,edit,1350631552
Control20=IDC_EDIUNO2,edit,1350631552
Control21=IDC_EDIDOS2,edit,1350631552
Control22=IDC_EDITRE2,edit,1350631552
Control23=IDC_EDICUA2,edit,1350631552
Control24=IDC_EDICIN2,edit,1350631552
Control25=IDC_LISCIC,combobox,1344339971
Control26=IDC_TEXSES,static,1342308352
Control27=IDC_EDISES,edit,1350631552
Control28=IDC_EDISES2,edit,1350631552
Control29=IDC_LISCHO,listbox,1352728833
Control30=IDC_LISCH2,listbox,1352728833
Control31=IDC_TEXSES3,static,1342308352
Control32=IDC_TEXSES4,static,1342308352

[CLS:CDlgLisACF]
Type=0
HeaderFile=lisacaview.h
ImplementationFile=lisacaview.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LISCRUHOR
VirtualFilter=dWC

[DLG:IDD_DLGCONAUL (Spanish (Mexican))]
Type=1
Class=CDlgConAul
ControlCount=44
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_TEXUNO,static,1342308352
Control11=IDC_TEXDOS,static,1342308352
Control12=IDC_TEXTRE,static,1342308352
Control13=IDC_TEXCUA,static,1342308352
Control14=IDC_TEXCIN,static,1342308352
Control15=IDC_EDIUNO,edit,1350631552
Control16=IDC_EDIDOS,edit,1350631552
Control17=IDC_EDICIN,edit,1350631552
Control18=IDC_EDICUA,edit,1350631552
Control19=IDC_EDITRE,edit,1350631552
Control20=IDC_LISAULAS,combobox,1344339971
Control21=IDC_TEXSEI,static,1342308352
Control22=IDC_EDISEI,edit,1350631552
Control23=IDC_TEXSIE,static,1342308352
Control24=IDC_EDISIE,edit,1350631552
Control25=IDC_TEXOCH,static,1342308352
Control26=IDC_EDIOCH,edit,1350631552
Control27=IDC_TEXNUE,static,1342308352
Control28=IDC_EDINUE,edit,1350631552
Control29=IDC_TEXDIE,static,1342308352
Control30=IDC_EDIDIE,edit,1350631552
Control31=IDC_TEXONC,static,1342308352
Control32=IDC_EDIONC,edit,1350631552
Control33=IDC_TEXDOC,static,1342308352
Control34=IDC_EDIDOC,edit,1350631552
Control35=IDC_TEXTRC,static,1342308352
Control36=IDC_EDITRC,edit,1350631552
Control37=IDC_TEXCAT,static,1342308352
Control38=IDC_EDICAT,edit,1350631552
Control39=IDC_TEXQUI,static,1342308352
Control40=IDC_EDIQUI,edit,1350631552
Control41=IDC_TEXDIS,static,1342308352
Control42=IDC_EDIDIS,edit,1350631552
Control43=IDC_TEXDIC,static,1342308352
Control44=IDC_EDIDIC,edit,1350631552

[CLS:CDlgConAul]
Type=0
HeaderFile=lisacaview.h
ImplementationFile=lisacaview.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDICAT
VirtualFilter=dWC

[DLG:IDD_DLGPOBINI (Spanish (Mexican))]
Type=1
Class=CDlgPobIni
ControlCount=7
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_LISPIN,listbox,1352728833
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[CLS:CDlgPobIni]
Type=0
HeaderFile=lisacaview.h
ImplementationFile=lisacaview.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgPobIni
VirtualFilter=dWC

[DLG:IDD_DLGPROADI (Spanish (Mexican))]
Type=1
Class=CDlgProAdi
ControlCount=41
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_LISPENCIC,listbox,1352728833
Control4=IDC_LISPENAUL,listbox,1352728833
Control5=IDC_LISPENDOC,listbox,1352728833
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_LISDOC,listbox,1352728833
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_LISPAC,listbox,1352728833
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_CALPEN,button,1342242816
Control21=IDC_GNPOBL,button,1342242816
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_LISSP3,listbox,1352728833
Control28=IDC_LISSP4,listbox,1352728833
Control29=IDC_LISSP1,listbox,1352728833
Control30=IDC_LISSP2,listbox,1352728833
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,static,1342308352
Control33=IDC_LISSUBPOB,listbox,1352728833
Control34=IDC_STATIC,static,1342308352
Control35=IDC_STATIC,static,1342308352
Control36=IDC_STATIC,static,1342308352
Control37=IDC_TOTPEN,edit,1342244992
Control38=IDC_STATIC,static,1342308352
Control39=IDC_NUMPOB,edit,1342244992
Control40=IDC_STATIC,static,1342308352
Control41=IDC_ALTASI,button,1342242816

[CLS:CDlgProAdi]
Type=0
HeaderFile=lisacaview.h
ImplementationFile=lisacaview.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgProAdi
VirtualFilter=dWC

