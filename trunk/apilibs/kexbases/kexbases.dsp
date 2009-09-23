# Microsoft Developer Studio Project File - Name="KernelEx Base Shared" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=KernelEx Base Shared - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "kexbases.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "kexbases.mak" CFG="KernelEx Base Shared - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "KernelEx Base Shared - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "KernelEx Base Shared - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "KernelEx Base Shared - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "KERNELEXBASESHARED_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /O2 /I "." /I "../../common" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D _WIN32_WINNT=0x0500 /YX /FD /TP /GF /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x415 /d "NDEBUG"
# ADD RSC /l 0x415 /i "../../common" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib version.lib ../../common/KernelEx.lib ../../kexcrt/kexcrt.lib libc.lib /nologo /dll /map /machine:I386 /nodefaultlib /ignore:4092 /OPT:NOWIN98
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "KernelEx Base Shared - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "KERNELEXBASESHARED_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /Zi /Od /I "." /I "../../common" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D _WIN32_WINNT=0x0500 /YX /FD /TP /GZ /GF /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x415 /d "_DEBUG"
# ADD RSC /l 0x415 /i "../../common" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib version.lib ../../common/KernelEx.lib ../../kexcrt/kexcrt.lib libc.lib /nologo /dll /map /debug /machine:I386 /nodefaultlib /ignore:4092 /OPT:NOWIN98
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "KernelEx Base Shared - Win32 Release"
# Name "KernelEx Base Shared - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "kernel32"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Kernel32\_kernel32_apilist.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\_kernel32_apilist.h
# End Source File
# Begin Source File

SOURCE=.\Kernel32\_kernel32_stubs.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\CopyFileEx.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\CreateThread_fix.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\DeleteCriticalSection.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\FileApis_fix.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\GetConsoleWindow.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\GetFileSizeEx.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\GlobalMemoryStatusEx.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\HeapLocks.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\InitializeCriticalSectionAndSpinCount.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\IsProcessorFeaturePresent.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\IsWow64Process.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\Jobs.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\KEXVersion.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\locale.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\locale_casemap.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\locale_collation.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\locale_fold.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\locale_sortkey.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\locale_unicode.h
# End Source File
# Begin Source File

SOURCE=.\Kernel32\locale_wctype.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\LockFileEx.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\MapViewOfFile.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\MoveFileExA.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\MoveFileWithProgressA.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\OpenThread.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\RemoteDesktop.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\SetFilePointerEx.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\TryEnterCriticalSection.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\uilang.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\unikernel32.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\version.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\VirtualAllocEx.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\volume.c
# End Source File
# Begin Source File

SOURCE=.\Kernel32\widecharconv.c
# End Source File
# End Group
# Begin Group "user32"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\User32\_user32_apilist.c
# End Source File
# Begin Source File

SOURCE=.\User32\_user32_apilist.h
# End Source File
# Begin Source File

SOURCE=.\User32\_user32_stubs.c
# End Source File
# Begin Source File

SOURCE=.\User32\CallWindowProcA_fix.c
# End Source File
# Begin Source File

SOURCE=.\User32\DisableProcessWindowsGhosting.c
# End Source File
# Begin Source File

SOURCE=.\User32\EnableWindow.c
# End Source File
# Begin Source File

SOURCE=.\User32\ForegroundWindow.c
# End Source File
# Begin Source File

SOURCE=.\User32\GetAncestor.c
# End Source File
# Begin Source File

SOURCE=.\User32\GetMouseMovePointsEx.c
# End Source File
# Begin Source File

SOURCE=.\User32\GetNextDlgTabItem_fix.c
# End Source File
# Begin Source File

SOURCE=.\User32\IsHungAppWindow.c
# End Source File
# Begin Source File

SOURCE=.\User32\LockWorkStation.c
# End Source File
# Begin Source File

SOURCE=.\User32\lstr.c
# End Source File
# Begin Source File

SOURCE=.\User32\MapVirtualKey_fix.c
# End Source File
# Begin Source File

SOURCE=.\User32\SendMessage_fix.c
# End Source File
# Begin Source File

SOURCE=.\User32\UberUSER.c
# End Source File
# Begin Source File

SOURCE=.\User32\uniuser32.c
# End Source File
# Begin Source File

SOURCE=.\User32\UpdateLayeredWindow.c
# End Source File
# End Group
# Begin Group "gdi32"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Gdi32\_gdi32_apilist.c
# End Source File
# Begin Source File

SOURCE=.\Gdi32\_gdi32_apilist.h
# End Source File
# Begin Source File

SOURCE=.\Gdi32\_gdi32_stubs.c
# End Source File
# Begin Source File

SOURCE=.\Gdi32\FontResourceExA.c
# End Source File
# Begin Source File

SOURCE=.\Gdi32\gdi9x.h
# End Source File
# Begin Source File

SOURCE=.\Gdi32\GetGlyphOutlineA_fix.c
# End Source File
# Begin Source File

SOURCE=.\Gdi32\TextOut.c
# End Source File
# Begin Source File

SOURCE=.\Gdi32\unigdi32.c
# End Source File
# End Group
# Begin Group "advapi32"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Advapi32\_advapi32_apilist.c
# End Source File
# Begin Source File

SOURCE=.\Advapi32\_advapi32_apilist.h
# End Source File
# Begin Source File

SOURCE=.\Advapi32\_advapi32_stubs.c
# End Source File
# Begin Source File

SOURCE=.\Advapi32\OpenSCManager_stub.c
# End Source File
# Begin Source File

SOURCE=.\Advapi32\RegDisablePredefinedCache.c
# End Source File
# Begin Source File

SOURCE=.\Advapi32\RegOpenCurrentUser.c
# End Source File
# Begin Source File

SOURCE=.\Advapi32\security.c
# End Source File
# Begin Source File

SOURCE=.\Advapi32\TraceMessage.c
# End Source File
# Begin Source File

SOURCE=.\Advapi32\uniadvapi32.c
# End Source File
# End Group
# Begin Group "comdlg32"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\comdlg32\_comdlg32_apilist.c
# End Source File
# Begin Source File

SOURCE=.\comdlg32\_comdlg32_apilist.h
# End Source File
# Begin Source File

SOURCE=.\comdlg32\PrintDlgEx.c
# End Source File
# End Group
# Begin Group "version"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\version\_version_apilist.c
# End Source File
# Begin Source File

SOURCE=.\version\_version_apilist.h
# End Source File
# Begin Source File

SOURCE=.\version\universion.c
# End Source File
# End Group
# Begin Group "shell32"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\shell32\_shell32_apilist.c
# End Source File
# Begin Source File

SOURCE=.\shell32\_shell32_apilist.h
# End Source File
# Begin Source File

SOURCE=.\shell32\_shell32_stubs.c
# End Source File
# Begin Source File

SOURCE=.\shell32\CommandLineToArgvW.c
# End Source File
# Begin Source File

SOURCE=.\shell32\IsUserAnAdmin.c
# End Source File
# End Group
# Begin Source File

SOURCE=.\common.c
# End Source File
# Begin Source File

SOURCE=.\kexbases.def

!IF  "$(CFG)" == "KernelEx Base Shared - Win32 Release"

# Begin Custom Build
OutDir=.\Release
WkspDir=.
InputPath=.\kexbases.def

"$(OutDir)\k32ord.lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cl /nologo /c /TC /DK32ORD_IMPLIB /Fo$(OutDir)\k32ord.obj "$(WkspDir)\common\k32ord.h" 
	link /DLL /NOENTRY /NOLOGO /IGNORE:4070 /MACHINE:IX86 /DEF:"$(WkspDir)\common\k32ord.def" /OUT:$(OutDir)\k32ord.dll /IMPLIB:$(OutDir)\k32ord.lib $(OutDir)\k32ord.obj 
	del $(OutDir)\k32ord.exp 
	del $(OutDir)\k32ord.obj 
	del $(OutDir)\k32ord.dll 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "KernelEx Base Shared - Win32 Debug"

# Begin Custom Build
OutDir=.\Debug
WkspDir=.
InputPath=.\kexbases.def

"$(OutDir)\k32ord.lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cl /nologo /c /TC /DK32ORD_IMPLIB /Fo$(OutDir)\k32ord.obj "$(WkspDir)\common\k32ord.h" 
	link /DLL /NOENTRY /NOLOGO /IGNORE:4070 /MACHINE:IX86 /DEF:"$(WkspDir)\common\k32ord.def" /OUT:$(OutDir)\k32ord.dll /IMPLIB:$(OutDir)\k32ord.lib $(OutDir)\k32ord.obj 
	del $(OutDir)\k32ord.exp 
	del $(OutDir)\k32ord.obj 
	del $(OutDir)\k32ord.dll 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\main.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\common.h
# End Source File
# Begin Source File

SOURCE=..\..\common\k32ord.def
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\common\k32ord.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\kexbases.rc
# End Source File
# End Group
# End Target
# End Project
