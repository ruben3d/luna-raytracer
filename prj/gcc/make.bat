@ECHO OFF

REM - make.bat
REM - win32 build system

ECHO.
ECHO Usage:
ECHO.
ECHO   make profile [target]
ECHO.
ECHO where:
ECHO.
ECHO   'profile' is debug or release.
ECHO   'target' is one of all, clean, deps, dist...
ECHO.

SET ARCH=win32
SET PROFILE=%1

ECHO Unix-like equivalent:
ECHO   ARCH=win32 PROFILE=%1 make %2
mingw32-make %2