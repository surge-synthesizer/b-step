#define MyAppPublisher "Surge Synth Team"
#define MyAppURL "https://www.surge-synth-team.org/"
#define MyAppName "B-Step"
#define MyAppNameCondensed "BStep"
#define MyID "9F829DB2-70CC-4FF0-8806-36A5C6C9E95D"

;uncomment these two lines if building the installer locally!
;#define BSTEP_SRC "..\..\"
;#define BSTEP_BIN "..\..\build\"

[Setup]
AppId={#MyID}
AppName={#MyAppName}
AppVersion={#BSTEP_VERSION}
AppVerName={#MyAppName} {#BSTEP_VERSION}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\{#MyAppPublisher}\{#MyAppName}\
DefaultGroupName={#MyAppName}
DisableDirPage=yes
DisableProgramGroupPage=yes
AlwaysShowDirOnReadyPage=yes
LicenseFile={#BSTEP_SRC}\LICENSE-gpl3
OutputBaseFilename={#MyAppName}-win32-{#BSTEP_VERSION}-setup
SetupIconFile={#BSTEP_SRC}\resources\installer_win\bstep.ico
UninstallDisplayIcon={uninstallexe}
UsePreviousAppDir=yes
Compression=lzma
SolidCompression=yes
UninstallFilesDir={autoappdata}\{#MyAppName}\uninstall
CloseApplicationsFilter=*.exe,*.vst3
WizardStyle=modern
WizardSizePercent=100
WizardImageFile={#BSTEP_SRC}\resources\installer_win\empty.bmp
WizardSmallImageFile={#BSTEP_SRC}\resources\installer_win\empty.bmp
WizardImageAlphaFormat=defined

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Types]
Name: "full"; Description: "Full installation"
Name: "plugin"; Description: "VST3 installation"
Name: "standalone"; Description: "Standalone installation"
Name: "custom"; Description: "Custom"; Flags: iscustom

[Components]
Name: "vst3"; Description: "{#MyAppNameCondensed} VST3 (32-bit)"; Types: full plugin custom
Name: "exe"; Description: "{#MyAppNameCondensed} Standalone (32-bit)"; Types: full standalone custom

[Files]
Source: "{#BSTEP_BIN}\bstep-products\{#MyAppName}.exe"; DestDir: "{app}"; Components: exe; Flags: ignoreversion
Source: "{#BSTEP_BIN}\bstep-products\{#MyAppName}.vst3\*"; DestDir: "{autocf}\VST3\{#MyAppName}.vst3\"; Components: vst3; Flags: ignoreversion recursesubdirs

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppName}.exe"; Flags: createonlyiffileexists
