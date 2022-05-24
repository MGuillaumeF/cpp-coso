@echo off

set DCMAKE_BUILD_TYPE=Debug
set DESTINATION_DIRECTORY=%~dp0../bin
cd ../
echo. GENERATE TARGET
cmake -G "Visual Studio 16 2019" -DBOOST_ROOT=C:/Users/miche/Desktop/boost_1_76_0 -B %DESTINATION_DIRECTORY%
echo.
@REM echo. BUILD TARGET
@REM call cmd.exe /C "cmake --build %DESTINATION_DIRECTORY% && cd %DESTINATION_DIRECTORY% && call ctest"
@REM "C:\Program Files\CMake\bin\cpack.exe" -G "NSIS;ZIP"
cd %~dp0
echo. END
pause
