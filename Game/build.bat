@echo on

:: Generate cmake project
cmake -B out .

:: Build the project
cmake --build out