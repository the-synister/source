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
    ${Else}
        StrCpy $InstDir "$ProgramFiles32\QULab\Synister"
    ${EndIf}
${EndIf}
FunctionEnd

;--------------------------------
;Installer Sections

Section "standalone" 

  SetOutPath "$INSTDIR"
  
  ;ADD YOUR OWN FILES HERE...
  File standalone-32\synister.exe
  
  ;Store installation folder
  WriteRegStr HKCU "Software\QULab\Synister" "" $INSTDIR
  
  ;Shortcut on desktop
  CreateShortCut "$DESKTOP\synister.lnk" "$INSTDIR\synister.exe"
SectionEnd


Section "vst64" 
${If} ${RunningX64}
  ReadRegStr $0 HKLM "SOFTWARE\VST" "VSTPluginsPath"
${Else}
  Goto No64Bit
${EndIf}

  SetOutPath "$0"
	
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
  File vst-64\synister.dll

No64Bit:
SectionEnd

Section "vst32" 
${If} ${RunningX64}
  ReadRegStr $0 HKLM "SOFTWARE\Wow6432Node\VST" "VSTPluginsPath"
${Else}
  ReadRegStr $0 HKLM "SOFTWARE\VST" "VSTPluginsPath"
${EndIf}

  SetOutPath "$0"
	
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
  File vst-32\synister.dll

  ;Create uninstaller
  WriteUninstaller "$INSTDIR\synister-uninstall.exe"
SectionEnd



;--------------------------------
;Uninstaller Section

Section "Uninstall"

  ;ADD YOUR OWN FILES HERE...

  Delete "$INSTDIR\synister.exe"
  RMDir "$INSTDIR"
  Delete "$DESKTOP\synister.lnk"

  ReadRegStr $0 HKCU "Software\QULab\SynisterVst32" ""
  Delete "$0\synister.dll"

  ReadRegStr $0 HKCU "Software\QULab\SynisterVst64" ""
  Delete "$0\synister.dll"

  DeleteRegKey /ifempty HKCU "Software\QULab\Synister"
  DeleteRegKey /ifempty HKCU "Software\QULab"

SectionEnd