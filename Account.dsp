# Microsoft Developer Studio Project File - Name="Account" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Account - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Account.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Account.mak" CFG="Account - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Account - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Account - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Account - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"bin/Account.exe"

!ELSEIF  "$(CFG)" == "Account - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"bin/Account_d.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Account - Win32 Release"
# Name "Account - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Account.cpp
# End Source File
# Begin Source File

SOURCE=.\Account.rc
# End Source File
# Begin Source File

SOURCE=.\Account1.cpp
# End Source File
# Begin Source File

SOURCE=.\AccountButton.cpp
# End Source File
# Begin Source File

SOURCE=.\AccountDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AccountInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AccountLogDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AccountManageDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AccountSelDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ado.cpp
# End Source File
# Begin Source File

SOURCE=.\DataBase.cpp
# End Source File
# Begin Source File

SOURCE=.\DataManageDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Des.cpp
# End Source File
# Begin Source File

SOURCE=.\InOutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\IntoAccountMoneyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MakeReportDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MoneyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MoneyMoveDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MoneyOper.cpp
# End Source File
# Begin Source File

SOURCE=.\MyList.cpp
# End Source File
# Begin Source File

SOURCE=.\Parameter.cpp
# End Source File
# Begin Source File

SOURCE=.\Pay.cpp
# End Source File
# Begin Source File

SOURCE=.\PayDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SearchDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\User.cpp
# End Source File
# Begin Source File

SOURCE=.\UserAccountDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UserLoginDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Account.h
# End Source File
# Begin Source File

SOURCE=.\Account1.h
# End Source File
# Begin Source File

SOURCE=.\AccountButton.h
# End Source File
# Begin Source File

SOURCE=.\AccountDlg.h
# End Source File
# Begin Source File

SOURCE=.\AccountInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\AccountLogDlg.h
# End Source File
# Begin Source File

SOURCE=.\AccountManageDlg.h
# End Source File
# Begin Source File

SOURCE=.\AccountSelDlg.h
# End Source File
# Begin Source File

SOURCE=.\ado.h
# End Source File
# Begin Source File

SOURCE=.\DataBase.h
# End Source File
# Begin Source File

SOURCE=.\DataManageDlg.h
# End Source File
# Begin Source File

SOURCE=.\Des.h
# End Source File
# Begin Source File

SOURCE=.\InOutDlg.h
# End Source File
# Begin Source File

SOURCE=.\IntoAccountMoneyDlg.h
# End Source File
# Begin Source File

SOURCE=.\MakeReportDlg.h
# End Source File
# Begin Source File

SOURCE=.\MoneyDlg.h
# End Source File
# Begin Source File

SOURCE=.\MoneyMoveDlg.h
# End Source File
# Begin Source File

SOURCE=.\MoneyOper.h
# End Source File
# Begin Source File

SOURCE=.\MyList.h
# End Source File
# Begin Source File

SOURCE=.\Parameter.h
# End Source File
# Begin Source File

SOURCE=.\Pay.h
# End Source File
# Begin Source File

SOURCE=.\PayDlg.h
# End Source File
# Begin Source File

SOURCE=.\ReportDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SearchDlg.h
# End Source File
# Begin Source File

SOURCE=.\SettingDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\User.h
# End Source File
# Begin Source File

SOURCE=.\UserAccountDlg.h
# End Source File
# Begin Source File

SOURCE=.\UserLoginDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Account.ico
# End Source File
# Begin Source File

SOURCE=.\res\Account.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Arrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ArrowLeft.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ArrowRight.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap11.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap12.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap13.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap14.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap15.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap17.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\blue_edi.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BlueDelete.ico
# End Source File
# Begin Source File

SOURCE=.\res\BlueEdit.ico
# End Source File
# Begin Source File

SOURCE=.\res\BlueNew.ico
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CompanyAccount.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CompanyAccount2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CompanyAccount3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\delete.bmp
# End Source File
# Begin Source File

SOURCE=.\res\delete1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EditDraw.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EditGet.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EditGet2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EditPay.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EditPay2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EmptyAccount.bmp
# End Source File
# Begin Source File

SOURCE=.\res\excel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\find.bmp
# End Source File
# Begin Source File

SOURCE=.\res\help.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Input.ico
# End Source File
# Begin Source File

SOURCE=.\res\Instruction.ico
# End Source File
# Begin Source File

SOURCE=.\res\lock.bmp
# End Source File
# Begin Source File

SOURCE=.\res\money_in.bmp
# End Source File
# Begin Source File

SOURCE=.\res\money_ou.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MoneyPay.ico
# End Source File
# Begin Source File

SOURCE=.\res\NewDraw.bmp
# End Source File
# Begin Source File

SOURCE=.\res\NewGet.bmp
# End Source File
# Begin Source File

SOURCE=.\res\NewGet2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\NewPay.bmp
# End Source File
# Begin Source File

SOURCE=.\res\NewPay2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\No.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ok.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Print2.ico
# End Source File
# Begin Source File

SOURCE=.\res\Question.bmp
# End Source File
# Begin Source File

SOURCE=.\res\red_del.bmp
# End Source File
# Begin Source File

SOURCE=.\res\red_edit.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RedEdit.ico
# End Source File
# Begin Source File

SOURCE=.\res\Report.ico
# End Source File
# Begin Source File

SOURCE=.\res\SetFields.ico
# End Source File
# Begin Source File

SOURCE=.\res\SuperMoney.ico
# End Source File
# Begin Source File

SOURCE=.\res\twoside.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TwoSide.ico
# End Source File
# Begin Source File

SOURCE=".\res\Yellow+.ico"
# End Source File
# Begin Source File

SOURCE=.\res\Yes.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Yes.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
