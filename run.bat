@echo off
setlocal

cd /d "%~dp0"
set "BUILD_DIR=%CD%\build"
set "EXECUTABLE=%BUILD_DIR%\bin\ComputacaoGrafica.exe"

where cmake >nul 2>&1
if errorlevel 1 (
    echo Erro: CMake nao encontrado no PATH.
    echo Instale o CMake e o Visual Studio Build Tools com Desenvolvimento para Desktop com C++.
    exit /b 1
)

echo [1/3] Configurando projeto...
cmake -S . -B "%BUILD_DIR%"
if errorlevel 1 exit /b 1

echo [2/3] Compilando projeto...
cmake --build "%BUILD_DIR%" --config Debug --target ComputacaoGrafica
if errorlevel 1 exit /b 1

if not exist "%EXECUTABLE%" (
    echo Erro: executavel nao encontrado em "%EXECUTABLE%".
    exit /b 1
)

echo [3/3] Executando ComputacaoGrafica...
"%EXECUTABLE%"
exit /b %errorlevel%
