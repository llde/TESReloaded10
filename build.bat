@echo off

@REM build project
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\msbuild" -target:NewVegasReloaded /property:Configuration=Release /property:Platform=x86 -m

@REM Copy dll & pdb
xcopy "NewVegasReloaded\Release\NewVegasReloaded.dll" "build\NewVegasReloaded\nvse\Plugins\" /y /d
xcopy "NewVegasReloaded\Release\NewVegasReloaded.pdb" "build\NewVegasReloaded\nvse\Plugins\" /y /d

@REM Copy config
xcopy "Extra\NewVegasReloaded.dll.config" "build\NewVegasReloaded\nvse\Plugins\" /y /d

@REM Copy Shaders
xcopy "Extra\Shaders\NewVegasReloaded\." "build\NewVegasReloaded\Shaders\NewVegasReloaded\" /y /d /s

@REM Copy to deploy if arg was passed
if "%~1" NEQ "" (
    echo deploying to "%~1"
    xcopy "build\NewVegasReloaded\." "%~1" /y /d /s
) else (
    echo "No deploy stage."
)

PAUSE