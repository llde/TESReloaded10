@echo off

@REM Arguments passed: Project name to build, and deploy location
SET "PROJECT=%~1"
SET "DEPLOY_LOCATION=%~2"

@REM Check arguments validity
if "%PROJECT%" NEQ "NewVegasReloaded" (
    if "%PROJECT%" NEQ "OblivionReloaded" (
        echo "Project %PROJECT% invalid. Use 'NewVegasReloaded' or 'OblivionReloaded'."
        PAUSE
        exit %ERRORLEVEL%
    )
)

@REM build project
msbuild -target:%PROJECT% /property:Configuration=Release /property:Platform=x86 -m

if %ERRORLEVEL% NEQ 0 (
    echo Build has failed. Deploy aborted.
    PAUSE
    exit %ERRORLEVEL%
)


@REM Copy dll & pdb
xcopy "%PROJECT%\Release\%PROJECT%.dll" "build\%PROJECT%\nvse\Plugins\" /y /d
xcopy "%PROJECT%\Release\%PROJECT%.pdb" "build\%PROJECT%\nvse\Plugins\" /y /d

@REM Copy config
xcopy "Extra\%PROJECT%.dll.config" "build\%PROJECT%\nvse\Plugins\" /y /d

@REM Copy Shaders
xcopy "Extra\Shaders\%PROJECT%\." "build\%PROJECT%\Shaders\%PROJECT%\" /y /d /s

@REM Copy to deploy if 2nd arg was passed
if "%DEPLOY_LOCATION%" NEQ "" (
    echo deploying to "%DEPLOY_LOCATION%"
    xcopy "build\%PROJECT%\." "%DEPLOY_LOCATION%" /y /d /s
) else (
    echo "No deploy stage."
)

PAUSE