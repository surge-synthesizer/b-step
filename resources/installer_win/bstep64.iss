#define MyAppPublisher "Surge Synth Team"
#define MyAppURL "https://www.surge-synth-team.org/"
#define MyAppName "B-Step"
#define MyAppNameCondensed "BStep"
#define MyID "9F829DB2-70CC-4FF0-8806-36A5C6C9E95C"

#ifndef MyAppVersion
#define MyAppVersion "0.0.0"
#endif

;uncomment these two lines if building the installer locally!
;#define BSTEP_SRC "..\..\"
;#define BSTEP_BIN "..\..\build\"

[Setup]
ArchitecturesInstallIn64BitMode=x64
ArchitecturesAllowed=x64
AppId={#MyID}
AppName={#MyAppName}
AppVerName={#MyAppName}
AppVersion={#MyAppVersion}
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
OutputBaseFilename={#MyAppNameCondensed}-{#MyAppVersion}-Windows-64bit-setup
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
Name: "clap"; Description: "CLAP installation"
Name: "vst3"; Description: "VST3 installation"
Name: "standalone"; Description: "Standalone installation"
Name: "custom"; Description: "Custom"; Flags: iscustom

[Components]
Name: "CLAP"; Description: "{#MyAppName} CLAP (64-bit)"; Types: full clap custom
Name: "VST3"; Description: "{#MyAppName} VST3 (64-bit)"; Types: full vst3 custom
Name: "SA"; Description: "{#MyAppName} Standalone (64-bit)"; Types: full standalone custom

[Files]
Source: "{#BSTEP_BIN}\bstep-products\{#MyAppName}.clap"; DestDir: "{autocf}\CLAP\{#MyAppPublisher}\"; Components: CLAP; Flags: ignoreversion
Source: "{#BSTEP_BIN}\bstep-products\{#MyAppName}.vst3\*"; DestDir: "{autocf}\VST3\{#MyAppPublisher}\{#MyAppName}.vst3\"; Components: VST3; Flags: ignoreversion recursesubdirs
Source: "{#BSTEP_BIN}\bstep-products\{#MyAppName}.exe"; DestDir: "{app}"; Components: SA; Flags: ignoreversion

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppName}.exe"; Flags: createonlyiffileexists
