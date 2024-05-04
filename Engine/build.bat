@echo off

:: Generate cmake project
cmake -DCMAKE_BUILD_TYPE=Release -B out .

:: Build the project
cmake --build out

@echo off
echo Press any key to close...
pause >nul