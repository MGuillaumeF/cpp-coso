rem cmake -S %~dp0../ -B %~dp0../bin -DCMAKE_BUILD_TYPE=Release
cmake --build %~dp0../bin > %~dp0../mvsc_warning_report.txt