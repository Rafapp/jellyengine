@echo off

:: Generate cmake project
cmake -DCMAKE_BUILD_TYPE=Release -B out .

:: Build the project
cmake --build out

set /p _= (Press any key...) >nul

echo.