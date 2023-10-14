@echo off

set UATBatFile=%~dp0..\..\..\Engine\Build\BatchFiles\RunUAT.bat
set ProjectFile=%~dp0..\..\..\GlassesShop\GlassesShop.uproject

set cmdline=%UATBatFile% BuildCookRun -project=%ProjectFile% -platform=Android -cookflavor=ASTC -noP4 -pak -unattended -compressed -stage -archive -utf8output -cook -build -package %*
echo cmdline=%cmdline%

call %cmdline%

pause