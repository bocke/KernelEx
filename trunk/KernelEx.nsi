  !define _VERSION '4.5 Beta 2'
  
  !ifndef _DEBUG
    !define FLAVOUR 'Release'
    !define VERSION '${_VERSION}'
  !else
    !define FLAVOUR 'Debug'
    !define VERSION '${_VERSION} Debug'
  !endif

;--------------------------------
;Includes

  !include "MUI2.nsh"
  !include "UpdateDLL.nsh"
  !include "WinVer.nsh"
  !include "nsDialogs.nsh"

;--------------------------------
;General

  SetCompressor /SOLID lzma
  
  ;Name and file
  Name "KernelEx"
  Caption "KernelEx ${VERSION} Setup"
  OutFile "..\KernelEx-dev.exe"

  ;Default installation folder
  InstallDir "$WINDIR\KernelEx"

  ;Get installation folder from registry if available
  InstallDirRegKey HKLM "Software\KernelEx" "InstallDir"

;--------------------------------
;Variables

  Var ENABLEBUTTON
  Var WARNING_TEXT

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING
;  !define MUI_FINISHPAGE_NOAUTOCLOSE
;  !define MUI_UNFINISHPAGE_NOAUTOCLOSE

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "License.txt"
  !insertmacro MUI_PAGE_INSTFILES
  Page custom PageDefConfig PageLeaveDefConfig
  !insertmacro MUI_PAGE_FINISH

  !insertmacro MUI_UNPAGE_WELCOME
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  !insertmacro MUI_UNPAGE_FINISH

;--------------------------------
;Languages

  !insertmacro MUI_LANGUAGE "English"
  
  LangString DESC_SHORTPRODUCT ${LANG_ENGLISH} "Microsoft Layer for Unicode"
  LangString DESC_LONGPRODUCT ${LANG_ENGLISH} "Microsoft Layer for Unicode on Windows 95, 98, and Me Systems, 1.1.3790.0"
  LangString DESC_PRODUCT_DECISION ${LANG_ENGLISH} "$(DESC_SHORTPRODUCT) is required.$\nIt is strongly \
    advised that you install$\n$(DESC_SHORTPRODUCT) before continuing.$\nIf you choose to continue, \
    you will need to connect$\nto the internet before proceeding.$\nWould you like to continue with \
    the installation?"
  LangString SEC_PRODUCT ${LANG_ENGLISH} "$(DESC_SHORTPRODUCT) "
  LangString DESC_INSTALLING ${LANG_ENGLISH} "Installing"
  LangString DESC_DOWNLOADING1 ${LANG_ENGLISH} "Downloading"
  LangString DESC_DOWNLOADFAILED ${LANG_ENGLISH} "Download Failed:"
  LangString ERROR_PRODUCT_INVALID_PATH ${LANG_ENGLISH} "The $(DESC_SHORTPRODUCT) Installation$\n\
    was not found in the following location:$\n"
  LangString ERROR_PRODUCT_FATAL ${LANG_ENGLISH} "A fatal error occurred during the installation$\n\
    of the $(DESC_SHORTPRODUCT)."
  LangString DESC_SETTINGS_PRESERVE ${LANG_ENGLISH} "Do you want to preserve custom settings?"

;--------------------------------
;Functions

Function PageDefConfig

  nsDialogs::Create /NOUNLOAD 1018
  Pop $0

  !insertmacro MUI_HEADER_TEXT "Default configuration" "Choose default configuration of KernelEx."
  nsDialogs::CreateItem /NOUNLOAD STATIC ${WS_VISIBLE}|${WS_CHILD}|${WS_CLIPSIBLINGS} 0 0 0 100% 40 "You can choose default KernelEx configuration here. This configuration will be used for all applications for which no other configuration is specified."
  Pop $R0
  
  nsDialogs::CreateItem /NOUNLOAD BUTTON ${BS_AUTORADIOBUTTON}|${BS_VCENTER}|${BS_MULTILINE}|${WS_VISIBLE}|${WS_CHILD}|${WS_CLIPSIBLINGS}|${WS_GROUP}|${WS_TABSTOP} 0 10 75 100% 30 "Enable KernelEx extensions for all applications (recommended)"
  Pop $ENABLEBUTTON
  ${NSD_OnClick} $ENABLEBUTTON ToggleWarning
  
  nsDialogs::CreateItem /NOUNLOAD BUTTON ${BS_AUTORADIOBUTTON}|${BS_TOP}|${BS_MULTILINE}|${WS_VISIBLE}|${WS_CHILD}|${WS_CLIPSIBLINGS} 0 10 105 100% 30 "Disable KernelEx extensions"
  Pop $R0
  ${NSD_OnClick} $R0 ToggleWarning
  
  nsDialogs::CreateItem /NOUNLOAD STATIC ${WS_CHILD}|${WS_CLIPSIBLINGS} 0 0 175 100% 40 "If you choose to disable KernelEx extensions, programs you run won't get extended API functions by default. You will have to enable KernelEx extensions individually for applications which require newer Windows versions. This choice is better if you're paranoid."
  Pop $WARNING_TEXT

  SendMessage $ENABLEBUTTON ${BM_SETCHECK} 1 0

  nsDialogs::Show

FunctionEnd

Function PageLeaveDefConfig

  SendMessage $ENABLEBUTTON ${BM_GETCHECK} 0 0 $R0
  ${If} $R0 == 1
	WriteRegDWORD HKLM "Software\KernelEx" "DisableExtensions" 0
  ${Else}
	WriteRegDWORD HKLM "Software\KernelEx" "DisableExtensions" 1
  ${EndIf}

FunctionEnd

Function ToggleWarning

	Pop $R0
	${If} $R0 == $ENABLEBUTTON
		ShowWindow $WARNING_TEXT ${SW_HIDE}
	${Else}
		ShowWindow $WARNING_TEXT ${SW_SHOW}
	${EndIf}

FunctionEnd

;--------------------------------
;Installer Section

Section "MSLU" SECPRODUCT

  !define URL_PRODUCT "http://download.microsoft.com/download/b/7/5/b75eace3-00e2-4aa0-9a6f-0b6882c71642/unicows.exe"

  IfFileExists $SYSDIR\unicows.dll 0 lbl_download
  
  ;check version
  GetDllVersion $SYSDIR\unicows.dll $R0 $R1
  IntOp $R2 $R0 / 0x00010000
  IntOp $R3 $R0 & 0x0000FFFF
  IntOp $R4 $R1 / 0x00010000
  IntOp $R5 $R1 & 0x0000FFFF
  StrCmp "1.1.3790.0" "$R2.$R3.$R4.$R5" lbl_Skip
  
  lbl_download:
  DetailPrint "$(DESC_DOWNLOADING1) $(DESC_SHORTPRODUCT)..."
  MessageBox MB_ICONEXCLAMATION|MB_YESNO|MB_DEFBUTTON2 "$(DESC_PRODUCT_DECISION)" /SD IDNO \
    IDYES +2 IDNO 0
  Abort
  ; Download
  AddSize 900
  nsisdl::download /TIMEOUT=30000 "${URL_PRODUCT}" "$TEMP\unicows.exe"
  Pop $0
  StrCmp "$0" "success" lbl_continue
    DetailPrint "$(DESC_DOWNLOADFAILED) $0"
    Abort
 
  lbl_continue:
  DetailPrint "$(DESC_INSTALLING) $(DESC_SHORTPRODUCT)..."
  Banner::show /NOUNLOAD "$(DESC_INSTALLING) $(DESC_SHORTPRODUCT)..."
  CreateDirectory "$INSTDIR\MSLU"
  ExecWait '"$TEMP\unicows.exe" /t:$INSTDIR\MSLU' $0
  Banner::destroy
  Delete "$TEMP\unicows.exe"
   
  ; obtain any error code and inform the user ($0)
  ; If nsExec is unable to execute the process,
  ; it will return "error"
  ; If the process timed out it will return "timeout"
  ; else it will return the return code from the executed process.
  StrCmp $0 "" lbl_Error
  StrCmp $0 "0" lbl_NoError
  ; all others are fatal
  DetailPrint "$(ERROR_PRODUCT_FATAL)[$0]"
  Goto lbl_commonError
 
  lbl_Error:
  DetailPrint "$(ERROR_PRODUCT_INVALID_PATH)"
  Goto lbl_commonError
  
  lbl_commonError:
  RMDir /r "$INSTDIR"
  Abort
 
  lbl_NoError:
  CopyFiles /SILENT "$INSTDIR\MSLU\unicows.dll" "$INSTDIR\mslu.tmp"
  Rename /REBOOTOK "$INSTDIR\mslu.tmp" "$SYSDIR\unicows.dll"

  lbl_Skip:

SectionEnd

Section "Install"

  SetDetailsView show

  ReadRegStr $0 HKLM "Software\Microsoft\Windows\CurrentVersion\RunServicesOnce" "KexNeedsReboot"
  IfErrors +5
    DetailPrint "Detected unfinished previous installation."
    DetailPrint "You have to restart the system in order to complete it before you can proceed."
    MessageBox MB_ICONSTOP|MB_OK "You have to restart the system first."
    Abort

  SetOutPath "$INSTDIR"
    
  SetOverwrite on
  File setup\${FLAVOUR}\setupkex.exe
  SetOverwrite lastused
  
!ifdef _DEBUG
  nsExec::ExecToLog '"$INSTDIR\setupkex.exe" "$INSTDIR\kernel32.bak"'
  Pop $0
!else
  ExecWait '"$INSTDIR\setupkex.exe" "$INSTDIR\kernel32.bak"' $0
  StrCmp $0 "" 0 +2
    StrCpy $0 "error"
!endif
  DetailPrint "    setup returned: $0"
  Delete "$INSTDIR\setupkex.exe"
  StrCmp $0 "0" +3
    RMDir "$INSTDIR"
    Abort
  
  ;Files to install
  
  ;UpdateDLL_Func params:
  ;$R4 - target; $R5 - tempdir; $R6 - register?; $R7 - source
  GetTempFileName $0 "$INSTDIR"
  File /oname=$0 "Core\${FLAVOUR}\KernelEx.dll"
  StrCpy $R4 "$INSTDIR\KernelEx.dll"
  StrCpy $R6 "0"
  StrCpy $R7 $0
  Call UpgradeDLL_Func
  
  GetTempFileName $0 "$INSTDIR"
  File /oname=$0 "apilibs\kexbases\${FLAVOUR}\kexbases.dll"
  StrCpy $R4 "$INSTDIR\kexbases.dll"
  StrCpy $R6 "0"
  StrCpy $R7 $0
  Call UpgradeDLL_Func
  
  GetTempFileName $0 "$INSTDIR"
  File /oname=$0 "apilibs\kexbasen\${FLAVOUR}\kexbasen.dll"
  StrCpy $R4 "$INSTDIR\kexbasen.dll"
  StrCpy $R6 "0"
  StrCpy $R7 $0
  Call UpgradeDLL_Func
  
  GetTempFileName $0 "$INSTDIR"
  File /oname=$0 "sheet\${FLAVOUR}\sheet.dll"
  StrCpy $R4 "$INSTDIR\sheet.dll"
  StrCpy $R6 "1"
  StrCpy $R7 $0
  Call UpgradeDLL_Func
  
  GetTempFileName $0 "$INSTDIR"
  File /oname=$0 "kexCOM\${FLAVOUR}\kexCOM.dll"
  StrCpy $R4 "$INSTDIR\kexCOM.dll"
  StrCpy $R6 "1"
  StrCpy $R7 $0
  Call UpgradeDLL_Func

  SetOverwrite on
  
  File apilibs\core.ini
  File apilibs\settings.reg
  File license.txt
  
  GetTempFileName $0 "$INSTDIR"
  File /oname=$0 auxiliary\msimg32.dll
  Delete "$INSTDIR\msimg32.dll"
  Rename /REBOOTOK $0  "$INSTDIR\msimg32.dll"
  WriteRegStr HKLM "Software\KernelEx\KnownDLLs" \
    "MSIMG32" "MSIMG32.DLL"
  
  GetTempFileName $0 "$INSTDIR"
  File /oname=$0 auxiliary\pdh.dll
  Delete "$INSTDIR\pdh.dll"
  Rename /REBOOTOK $0  "$INSTDIR\pdh.dll"
  WriteRegStr HKLM "Software\KernelEx\KnownDLLs" \
    "PDH" "PDH.DLL"
  
  GetTempFileName $0 "$INSTDIR"
  File /oname=$0 auxiliary\psapi.dll
  Delete "$INSTDIR\psapi.dll"
  Rename /REBOOTOK $0  "$INSTDIR\psapi.dll"
  WriteRegStr HKLM "Software\KernelEx\KnownDLLs" \
    "PSAPI" "PSAPI.DLL"
  
  GetTempFileName $0 "$INSTDIR"
  File /oname=$0 auxiliary\uxtheme.dll
  Delete "$INSTDIR\uxtheme.dll"
  Rename /REBOOTOK $0  "$INSTDIR\uxtheme.dll"
  WriteRegStr HKLM "Software\KernelEx\KnownDLLs" \
    "UXTHEME" "UXTHEME.DLL"
  
  GetTempFileName $0 "$INSTDIR"
  File /oname=$0 auxiliary\wtsapi32.dll
  Delete "$INSTDIR\wtsapi32.dll"
  Rename /REBOOTOK $0  "$INSTDIR\wtsapi32.dll"
  WriteRegStr HKLM "Software\KernelEx\KnownDLLs" \
    "WTSAPI32" "WTSAPI32.DLL"
  
  GetTempFileName $0 "$INSTDIR"
  File /oname=$0 auxiliary\userenv.dll
  Delete "$INSTDIR\userenv.dll"
  Rename /REBOOTOK $0  "$INSTDIR\userenv.dll"
  WriteRegStr HKLM "Software\KernelEx\KnownDLLs" \
    "USERENV" "USERENV.DLL"
  
  SetOverwrite lastused
  
  ExecWait '"$WINDIR\regedit.exe" /s "$INSTDIR\settings.reg"'
  Delete "$INSTDIR\settings.reg"

  ;Store installation folder
  WriteRegStr HKLM "Software\KernelEx" "InstallDir" $INSTDIR
  
  ;Store run key
  WriteRegStr HKLM "System\CurrentControlSet\Control\MPRServices\KernelEx" "DLLName" "$INSTDIR\KernelEx.dll"
  WriteRegStr HKLM "System\CurrentControlSet\Control\MPRServices\KernelEx" "EntryPoint" "_MprStart@4"
  WriteRegDWORD HKLM "System\CurrentControlSet\Control\MPRServices\KernelEx" "StackSize" 0x1000
  
  ;Store uninstaller key
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\KernelEx" "DisplayName" "KernelEx ${VERSION}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\KernelEx" "UninstallString" '"$INSTDIR\uninstall.exe"'
  
  ;Write verifier
  SetOverWrite on
  File verify\${FLAVOUR}\verify.exe
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Run" \
    "KexVerify" "$INSTDIR\verify.exe"
  SetOverwrite lastused
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\RunServicesOnce" "KexNeedsReboot" ""
  SetRebootFlag true

SectionEnd

;--------------------------------
;Uninstaller Section

Section "Uninstall"

  SetDetailsView show

  ReadRegStr $0 HKLM "Software\Microsoft\Windows\CurrentVersion\RunServicesOnce" "KexNeedsReboot"
  IfErrors +5
    DetailPrint "Detected unfinished previous installation."
    DetailPrint "You have to restart the system in order to complete it before you can proceed."
    MessageBox MB_ICONSTOP|MB_OK "You have to restart the system first."
    Abort
  
  ;Files to uninstall
  IfFileExists "$INSTDIR\kernel32.bak" 0 +5
    GetTempFileName $0 "$SYSDIR"
    Delete $0
    Rename "$INSTDIR\kernel32.bak" $0
    Rename /REBOOTOK $0 "$SYSDIR\kernel32.dll"

  Delete /REBOOTOK "$INSTDIR\KernelEx.dll"
  Delete /REBOOTOK "$INSTDIR\kexbases.dll"
  Delete /REBOOTOK "$INSTDIR\kexbasen.dll"
  Delete "$INSTDIR\core.ini"
  UnRegDLL "$INSTDIR\sheet.dll"
  Delete /REBOOTOK "$INSTDIR\sheet.dll"
  UnRegDLL "$INSTDIR\kexCOM.dll"
  Delete /REBOOTOK "$INSTDIR\kexCOM.dll"
  Delete "$INSTDIR\license.txt"
  
  Delete /REBOOTOK "$INSTDIR\msimg32.dll"
  DeleteRegValue HKLM "Software\KernelEx\KnownDLLs" "MSIMG32"
  Delete /REBOOTOK "$INSTDIR\pdh.dll"
  DeleteRegValue HKLM "Software\KernelEx\KnownDLLs" "PDH"
  Delete /REBOOTOK "$INSTDIR\psapi.dll"
  DeleteRegValue HKLM "Software\KernelEx\KnownDLLs" "PSAPI"
  Delete /REBOOTOK "$INSTDIR\uxtheme.dll"
  DeleteRegValue HKLM "Software\KernelEx\KnownDLLs" "UXTHEME"
  Delete /REBOOTOK "$INSTDIR\wtsapi32.dll"
  DeleteRegValue HKLM "Software\KernelEx\KnownDLLs" "WTSAPI32"
  Delete /REBOOTOK "$INSTDIR\userenv.dll"
  DeleteRegValue HKLM "Software\KernelEx\KnownDLLs" "USERENV"
  
  Delete "$INSTDIR\verify.exe"
  DeleteRegValue HKLM "Software\Microsoft\Windows\CurrentVersion\Run" "KexVerify"

  Delete "$INSTDIR\Uninstall.exe"

  RMDir /r "$INSTDIR\MSLU"
  WriteINIStr $WINDIR\wininit.ini Rename DIRNUL $INSTDIR

  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "$(DESC_SETTINGS_PRESERVE)" IDYES +2 IDNO 0
    DeleteRegKey HKLM "Software\KernelEx"
  
  DeleteRegKey HKLM "System\CurrentControlSet\Control\MPRServices\KernelEx"
  DeleteRegKey /ifempty HKLM "System\CurrentControlSet\Control\MPRServices"
  
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\KernelEx"
  
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\RunServicesOnce" "KexNeedsReboot" ""
  SetRebootFlag true

SectionEnd

;--------------------------------
;.onInit

Function .onInit

  ${If} ${IsWin98}
  ${OrIf} ${IsWinME}
  Goto lbl_Ok
  ${EndIf}
  
  MessageBox MB_ICONSTOP|MB_OK "This program requires Windows 98 or Windows Millennium."
  Abort
  
  lbl_Ok:

 FunctionEnd
