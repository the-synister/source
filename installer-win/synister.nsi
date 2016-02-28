;NSIS Modern User Interface
;Basic Example Script
;Written by Joost Verburg

;--------------------------------
;Include Modern UI
  !include "MUI.nsh"

;--------------------------------
; 64 bit

  !include "x64.nsh"

;--------------------------------
;General

  ;Name and file
  Name "synister"
  OutFile "synister-install.exe"

  ;Default installation folder
  ;InstallDir "$PROGRAMFILES\QULab\Synister"
  
  ;Get installation folder from registry if available
  ;InstallDirRegKey HKCU "Software\QULab\Synister" ""

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING
  
;--------------------------------
;Pages

  !insertmacro MUI_PAGE_LICENSE "COPYING"
; !insertmacro MUI_PAGE_COMPONENTS
  !define MUI_PAGE_CUSTOMFUNCTION_SHOW DirectoryShow
  !define MUI_PAGE_CUSTOMFUNCTION_LEAVE DirectoryLeave
  !insertmacro MUI_PAGE_DIRECTORY
  !define MUI_PAGE_CUSTOMFUNCTION_SHOW DirectoryShow
  !define MUI_PAGE_CUSTOMFUNCTION_LEAVE DirectoryLeave
  !insertmacro MUI_PAGE_DIRECTORY
  !define MUI_PAGE_CUSTOMFUNCTION_SHOW DirectoryShow
  !define MUI_PAGE_CUSTOMFUNCTION_LEAVE DirectoryLeave
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  
;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"


Function .onInit
  ${If} $InstDir == "" ; Don't override setup.exe /D=c:\custom\dir
    ${If} ${RunningX64}
	  SetRegView 64
      StrCpy $InstDir "$ProgramFiles64\QULab\Synister"
	  ; standalone
      StrCpy $2 "$ProgramFiles64\QULab\Synister"
      ; vst 32
      ReadRegStr $3 HKLM "SOFTWARE\Wow6432Node\VST" "VSTPluginsPath"
      ; vst 64
      ReadRegStr $4 HKLM "SOFTWARE\VST" "VSTPluginsPath"
    ${Else}
      StrCpy $InstDir "$ProgramFiles32\QULab\Synister"
	  ; standalone
      StrCpy $2 "$ProgramFiles32\QULab\Synister"
      ; vst 32
      ReadRegStr $3 HKLM "SOFTWARE\VST" "VSTPluginsPath"
    ${EndIf}
  ${EndIf}
  ; reg 9 used to switch the directory pages
  StrCpy $9 "standalone"
FunctionEnd

 
Function DirectoryShow
  StrCmp $9 "standalone" StandalonePage
  StrCmp $9 "vst32" Vst32Page
  StrCmp $9 "vst64" Vst64Page
  Goto EndDirectoryShow

StandalonePage:
  !insertmacro MUI_INNERDIALOG_TEXT 1041 "Destination Folder"
  !insertmacro MUI_INNERDIALOG_TEXT 1019 "$2"
  !insertmacro MUI_INNERDIALOG_TEXT 1006 "Setup will install synister - Standalone in the following folder.$\r$\n$\r$\nTo install in a different folder, click Browse and select another folder. Click Next to continue."
  Goto EndDirectoryShow
 
Vst32Page:
  !insertmacro MUI_HEADER_TEXT "Choose Plugin Location" "Choose the folder in which to install synister - VST 32."
  !insertmacro MUI_INNERDIALOG_TEXT 1041 "VST 32 Destination Folder"
  !insertmacro MUI_INNERDIALOG_TEXT 1019 "$3"
  !insertmacro MUI_INNERDIALOG_TEXT 1006 "Setup will install synister - VST 32 bit in the following folder.$\r$\n$\r$\nTo install in a different folder, click Browse and select another folder. Click Install to start the installation."
  Goto EndDirectoryShow

Vst64Page:
  !insertmacro MUI_HEADER_TEXT "Choose Plugin Location" "Choose the folder in which to install synister - VST 64."
  !insertmacro MUI_INNERDIALOG_TEXT 1041 "VST 64 Destination Folder"
  !insertmacro MUI_INNERDIALOG_TEXT 1019 "$4"
  !insertmacro MUI_INNERDIALOG_TEXT 1006 "Setup will install synister - VST 64 bit in the following folder.$\r$\n$\r$\nTo install in a different folder, click Browse and select another folder. Click Install to start the installation."
  Goto EndDirectoryShow

EndDirectoryShow: 				
FunctionEnd
 
Function DirectoryLeave
  StrCmp $9 "standalone" SaveStandaloneDir
  StrCmp $9 "vst32" SaveVst32Dir
  StrCmp $9 "vst64" SaveVst64Dir
  Goto EndDirectoryLeave
 
SaveStandaloneDir:
  StrCpy $2 $INSTDIR
  StrCpy $9 "vst32"
  Goto EndDirectoryLeave
 
SaveVst32Dir:
  StrCpy $3 $INSTDIR
  StrCpy $9 "vst64"
  Goto EndDirectoryLeave
 
SaveVst64Dir:
  StrCpy $4 $INSTDIR
  Goto EndDirectoryLeave

EndDirectoryLeave:
FunctionEnd
 

;--------------------------------
;Installer Sections

Section "standalone" 
  SetOutPath "$2"
  
  ;ADD YOUR OWN FILES HERE...
  File synister.exe
  
  ;Store installation folder
  WriteRegStr HKCU "Software\QULab\Synister" "" $2
  
  ;Shortcut on desktop
  CreateShortCut "$DESKTOP\synister.lnk" "$2\synister.exe"

  ;Shortcut in start menu
  CreateDirectory "$SMPROGRAMS\QU Lab"
  CreateShortCut "$SMPROGRAMS\QU Lab\synister.lnk" "$2\synister.exe"
  CreateShortCut "$SMPROGRAMS\QU Lab\uninstall.lnk" "$2\synister-uninstall.exe"

  ;Create uninstaller
  WriteUninstaller "$2\synister-uninstall.exe"
SectionEnd


Section "vst32" 
  SetOutPath "$3"
	
  StrLen $0 $OUTDIR
  IntCmp $0 3 VstNotFound32 VstNotFound32 CheckPath32

  CheckPath32:
  IfFileExists $OUTDIR\*.* VstFound32 VstNotFound32
  VstFound32:
	Goto VstDone32
  VstNotFound32:
    SetOutPath "$PROGRAMFILES\VstPlugins"
${If} ${RunningX64}
    WriteRegStr HKLM "Software\Wow6432Node\VST" "VSTPluginsPath" $OUTDIR
${Else}
    WriteRegStr HKLM "Software\VST" "VSTPluginsPath" $OUTDIR
${EndIf}
	Goto VstDone32
  VstDone32:

  ;Store installation folder
  WriteRegStr HKCU "Software\QULab\SynisterVst32" "" $OUTDIR
  
  ;ADD YOUR OWN FILES HERE...
  File synister.dll
SectionEnd


Section "vst64" 
${If} ${RunningX64}
${Else}
  Goto No64Bit
${EndIf}
  SetOutPath "$4"
	
  StrLen $0 $OUTDIR
  IntCmp $0 3 VstNotFound64 VstNotFound64 CheckPath64

  CheckPath64:
  IfFileExists $OUTDIR\*.* VstFound64 VstNotFound64
  VstFound64:
	Goto VstDone64
  VstNotFound64:
    SetOutPath "$PROGRAMFILES\VstPlugins64"
    WriteRegStr HKLM "Software\VST" "VSTPluginsPath" $OUTDIR
	Goto VstDone64
  VstDone64:

  ;Store installation folder
  WriteRegStr HKCU "Software\QULab\SynisterVst64" "" $OUTDIR
  
  ;ADD YOUR OWN FILES HERE...
  File synister64.dll

No64Bit:
SectionEnd



;--------------------------------
;Uninstaller Section

Section "Uninstall"
 
  Delete "$DESKTOP\synister.lnk"
  Delete "$SMPROGRAMS\QU Lab\synister.lnk"
  Delete "$SMPROGRAMS\QU Lab\uninstall.lnk"
  RMDir "$SMPROGRAMS\QU Lab"

  ReadRegStr $0 HKCU "Software\QULab\SynisterVst32" ""
  Delete "$0\synister.dll"

  ReadRegStr $0 HKCU "Software\QULab\SynisterVst64" ""
  Delete "$0\synister64.dll"

  ReadRegStr $0 HKCU "Software\QULab\Synister" ""
  Delete "$0\synister.exe"
  Delete "$0\synister-uninstall.exe"
  RMDir "$0"

  DeleteRegKey /ifempty HKCU "Software\QULab\Synister"
  DeleteRegKey /ifempty HKCU "Software\QULab"
SectionEnd