#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/build"
EXECUTABLE="$BUILD_DIR/bin/ComputacaoGrafica"

cd "$SCRIPT_DIR"

if ! command -v cmake >/dev/null 2>&1; then
    echo "Erro: CMake nao encontrado."
    echo "Ubuntu/Debian: sudo apt install cmake build-essential freeglut3-dev libgl1-mesa-dev"
    exit 1
fi

if ! command -v c++ >/dev/null 2>&1 && ! command -v g++ >/dev/null 2>&1; then
    echo "Erro: compilador C++ nao encontrado."
    echo "Ubuntu/Debian: sudo apt install build-essential"
    exit 1
fi

echo "[1/3] Configurando projeto..."
cmake -S "$SCRIPT_DIR" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Debug

echo "[2/3] Compilando projeto..."
cmake --build "$BUILD_DIR" --config Debug --target ComputacaoGrafica

if [[ ! -x "$EXECUTABLE" ]]; then
    echo "Erro: executavel nao encontrado em $EXECUTABLE"
    exit 1
fi

echo "[3/3] Executando ComputacaoGrafica..."
exec "$EXECUTABLE"
