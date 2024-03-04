@echo off

:: Generate cmake project
cmake -B out .

:: Build the project
cmake --build out

:: Move the generated DLL to the current directory
move out\debug\JellyEngine.dll .

:: Clean up build artifacts
rmdir /s /q out