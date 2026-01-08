@echo off
echo ===================================
echo   Building and starting Pong (Windows)
echo ===================================

if not exist build mkdir build
cd build

cmake .. -G "Visual Studio 17 2022" -A x64

if %errorlevel% neq 0 (
    echo.
    echo ОШИБКА: CMake configuration error
    pause
    exit /b %errorlevel%
)

cmake --build . --config Release

if %errorlevel% neq 0 (
    echo.
    echo FAIL: Build failed
    pause
    exit /b %errorlevel%
)

echo.
echo Succesfully builded!
echo Game start...

cd Release
Pong.exe
