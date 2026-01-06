@echo off
echo ===================================
echo   Сборка и запуск Pong (Windows)
echo ===================================

if not exist build mkdir build
cd build

cmake .. -G "Visual Studio 17 2022" -A x64

if %errorlevel% neq 0 (
    echo.
    echo ОШИБКА: CMake конфигурация не удалась
    pause
    exit /b %errorlevel%
)

cmake --build . --config Release

if %errorlevel% neq 0 (
    echo.
    echo ОШИБКА: Сборка не удалась!
    pause
    exit /b %errorlevel%
)

echo.
echo Сборка завершена успешно!
echo Запуск игры...

Release\Pong.exe
