cmake -S %~dp0../ -B %~dp0../bin -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build %~dp0../bin --config Debug
rem > %~dp0../reports/msvc_warning_report.txt 2>&1