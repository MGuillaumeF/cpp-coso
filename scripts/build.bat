@echo off

set DCMAKE_GENERATOR="MinGW Makefiles"
set DCMAKE_CXX_COMPILER=clang++.exe
set DCMAKE_C_COMPILER=clang.exe
set DCMAKE_MAKE_PROGRAM=mingw32-make.exe
set DEXTERNAL_LIBS=C:/Users/miche/Desktop/boost_1_76_0/stage/lib/libboost_date_time-clangw13-mt-gd-x64-1_76.lib

set DCMAKE_BUILD_TYPE=Debug
set DESTINATION_DIRECTORY=%~dp0../bin
cd ../
echo. GENERATE TARGET
cmake -G %DCMAKE_GENERATOR% -DCMAKE_CXX_COMPILER=%DCMAKE_CXX_COMPILER% -DCMAKE_C_COMPILER=%DCMAKE_C_COMPILER% -DCMAKE_MAKE_PROGRAM=%DCMAKE_MAKE_PROGRAM% -DBOOST_ROOT=C:/Users/miche/Desktop/boost_1_76_0 -DCMAKE_BUILD_TYPE=%DCMAKE_BUILD_TYPE% -DEXTERNAL_LIBS:STRING=%DEXTERNAL_LIBS% -B %DESTINATION_DIRECTORY%
echo.
echo. BUILD TARGET
call cmd.exe /C "cmake --build %DESTINATION_DIRECTORY% && cd %DESTINATION_DIRECTORY% && call ctest"
"C:\Program Files\CMake\bin\cpack.exe" -G "NSIS;ZIP"
cd %~dp0
echo. END
pause
