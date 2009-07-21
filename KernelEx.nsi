  !define VERSION '4.0 RC 2'

;--------------------------------
;Includes

  !include "MUI2.nsh"
  !include "UpdateDLL.nsh"
  !include "WinVer.nsh"

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
;Interface Settings

  !define MUI_ABORTWARNING
;  !define MUI_FINISHPAGE_NOAUTOCLOSE
;  !define MUI_UNFINISHPAGE_NOAUTOCLOSE

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "License.txt"
  !insertmacro MUI_PAGE_INSTFILES
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
  LangString DESC_PRODUCT_TIMEOUT ${LANG_ENGLISH} "The installation of the $(DESC_SHORTPRODUCT) \
    has timed out."
  LangString ERROR_PRODUCT_INVALID_PATH ${LANG_ENGLISH} "The $(DESC_SHORTPRODUCT) Installation$\n\
    was not found in the following location:$\n"
  LangString ERROR_PRODUCT_FATAL ${LANG_ENGLISH} "A fatal error occurred during the installation$\n\
    of the $(DESC_SHORTPRODUCT)."
  LangString DESC_SETTINGS_PRESERVE ${LANG_ENGLISH} "Do you want to preserve custom settings?"
  
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
  nsExec::Exec '"$TEMP\unicows.exe" /t:$INSTDIR\MSLU'
  Pop $0
  Banner::destroy
  Delete "$TEMP\unicows.exe"
   
  ; obtain any error code and inform the user ($0)
  ; If nsExec is unable to execute the process,
  ; it will return "error"
  ; If the process timed out it will return "timeout"
  ; else it will return the return code from the executed process.
  StrCmp $0 "" lbl_NoError
  StrCmp $0 "0" lbl_NoError
  StrCmp $0 "error" lbl_Error
  StrCmp $0 "timeout" lbl_TimeOut
  ; all others are fatal
  DetailPrint "$(ERROR_PRODUCT_FATAL)[$0]"
  Goto lbl_commonError
 
  lbl_TimeOut:
  DetailPrint "$(DESC_PRODUCT_TIMEOUT)"
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
  SetOutPath "$INSTDIR"
    
  SetOverwrite on
  File setup\Release\setupkex.exe
  SetOverwrite lastused
  
  nsExec::ExecToLog '"$INSTDIR\setupkex.exe" "$INSTDIR\kernel32.bak"'
  Pop $0
  DetailPrint "    setup returned: $0"
  Delete "$INSTDIR\setupkex.exe"
  StrCmp $0 "0" +3
    RMDir "$INSTDIR"
    Abort
  
  ;Files to install
  
  ;UpdateDLL_Func params:
  ;$R4 - target; $R5 - tempdir; $R6 - register?; $R7 - source
  GetTempFileName $0 "$INSTDIR"
  File /oname=$0 "Core\Release\KernelEx.dll"
  StrCpy $R4 "$INSTDIR\KernelEx.dll"
  StrCpy $R6 "0"
  StrCpy $R7 $0
  Call UpgradeDLL_Func
  
  GetTempFileName $0 "$INSTDIR"
  File /oname=$0 "apilibs\kexbases\Release\kexbases.dll"
  StrCpy $R4 "$INSTDIR\kexbases.dll"
  StrCpy $R6 "0"
  StrCpy $R7 $0
  Call UpgradeDLL_Func
  
  GetTempFileName $0 "$INSTDIR"
  File /oname=$0 "apilibs\kexbasen\Release\kexbasen.dll"
  StrCpy $R4 "$INSTDIR\kexbasen.dll"
  StrCpy $R6 "0"
  StrCpy $R7 $0
  Call UpgradeDLL_Func
  
  GetTempFileName $0 "$INSTDIR"
  File /oname=$0 "sheet\Release\sheet.dll"
  StrCpy $R4 "$INSTDIR\sheet.dll"
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
  WriteRegStr HKLM "System\CurrentControlSet\Control\SessionManager\KnownDLLs" \
    "MSIMG32" "..\KernelEx\msimg32.dll"
  
  GetTempFileName $0 "$INSTDIR"
  File /oname=$0 auxiliary\pdh.dll
  Delete "$INSTDIR\pdh.dll"
  Rename /REBOOTOK $0  "$INSTDIR\pdh.dll"
  WriteRegStr HKLM "System\CurrentControlSet\Control\SessionManager\KnownDLLs" \
    "PDH" "..\KernelEx\pdh.dll"
  
  GetTempFileName $0 "$INSTDIR"
  File /oname=$0 auxiliary\psapi.dll
  Delete "$INSTDIR\psapi.dll"
  Rename /REBOOTOK $0  "$INSTDIR\psapi.dll"
  WriteRegStr HKLM "System\CurrentControlSet\Control\SessionManager\KnownDLLs" \
    "PSAPI" "..\KernelEx\psapi.dll"
  
  GetTempFileName $0 "$INSTDIR"
  File /oname=$0 auxiliary\uxtheme.dll
  Delete "$INSTDIR\uxtheme.dll"
  Rename /REBOOTOK $0  "$INSTDIR\uxtheme.dll"
  WriteRegStr HKLM "System\CurrentControlSet\Control\SessionManager\KnownDLLs" \
    "UXTHEME" "..\KernelEx\uxtheme.dll"
  
  GetTempFileName $0 "$INSTDIR"
  File /oname=$0 auxiliary\wtsapi32.dll
  Delete "$INSTDIR\wtsapi32.dll"
  Rename /REBOOTOK $0  "$INSTDIR\wtsapi32.dll"
  WriteRegStr HKLM "System\CurrentControlSet\Control\SessionManager\KnownDLLs" \
    "WTSAPI32" "..\KernelEx\wtsapi32.dll"
  
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
  File verify\Release\verify.exe
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Run" \
    "KexVerify" "$INSTDIR\verify.exe"
  SetOverwrite lastused
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

  SetRebootFlag true

SectionEnd

;--------------------------------
;Uninstaller Section

Section "Uninstall"

  SetDetailsView show
  
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "$(DESC_SETTINGS_PRESERVE)" IDYES +2 IDNO 0
    DeleteRegKey HKLM "Software\KernelEx"
  
  DeleteRegKey HKLM "System\CurrentControlSet\Control\MPRServices\KernelEx"
  DeleteRegKey /ifempty HKLM "System\CurrentControlSet\Control\MPRServices"
  
  ;Files to uninstall
  Rename /REBOOTOK "$INSTDIR\kernel32.bak" "$SYSDIR\kernel32.dll"
  Delete /REBOOTOK "$INSTDIR\KernelEx.dll"
  Delete /REBOOTOK "$INSTDIR\kexbases.dll"
  Delete /REBOOTOK "$INSTDIR\kexbasen.dll"
  Delete "$INSTDIR\core.ini"
  UnRegDLL "$INSTDIR\sheet.dll"
  Delete /REBOOTOK "$INSTDIR\sheet.dll"
  Delete "$INSTDIR\license.txt"
  
  Delete /REBOOTOK "$INSTDIR\msimg32.dll"
  DeleteRegValue HKLM "System\CurrentControlSet\Control\SessionManager\KnownDLLs" "MSIMG32"
  Delete /REBOOTOK "$INSTDIR\pdh.dll"
  DeleteRegValue HKLM "System\CurrentControlSet\Control\SessionManager\KnownDLLs" "PDH"
  Delete /REBOOTOK "$INSTDIR\psapi.dll"
  DeleteRegValue HKLM "System\CurrentControlSet\Control\SessionManager\KnownDLLs" "PSAPI"
  Delete /REBOOTOK "$INSTDIR\uxtheme.dll"
  DeleteRegValue HKLM "System\CurrentControlSet\Control\SessionManager\KnownDLLs" "UXTHEME"
  Delete /REBOOTOK "$INSTDIR\wtsapi32.dll"
  DeleteRegValue HKLM "System\CurrentControlSet\Control\SessionManager\KnownDLLs" "WTSAPI32"
  
  Delete "$INSTDIR\verify.exe"
  DeleteRegValue HKLM "Software\Microsoft\Windows\CurrentVersion\Run" "KexVerify"

  Delete "$INSTDIR\Uninstall.exe"

  RMDir /r "$INSTDIR\MSLU"
  WriteINIStr $WINDIR\wininit.ini Rename DIRNUL $INSTDIR

  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\KernelEx"
  
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
