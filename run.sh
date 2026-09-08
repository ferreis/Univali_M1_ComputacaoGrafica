#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/build"
EXECUTABLE="$BUILD_DIR/bin/ComputacaoGrafica"

cd "$SCRIPT_DIR"

instalar_dependencias_debian() {
    local pacotes=(
        cmake
        build-essential
        libglut-dev
        libgl1-mesa-dev
    )
    local faltando=()

    for pacote in "${pacotes[@]}"; do
        if ! dpkg-query -W -f='${Status}' "$pacote" 2>/dev/null | grep -q "ok installed"; then
            faltando+=("$pacote")
        fi
    done

    if (( ${#faltando[@]} == 0 )); then
        return
    fi

    echo "Dependencias ausentes: ${faltando[*]}"
    echo "Instalando dependencias necessarias..."

    if [[ ${EUID:-$(id -u)} -eq 0 ]]; then
        apt-get update
        apt-get install -y "${faltando[@]}"
    else
        if ! command -v sudo >/dev/null 2>&1; then
            echo "Erro: sudo nao encontrado."
            echo "Instale manualmente: ${faltando[*]}"
            exit 1
        fi

        sudo apt-get update
        sudo apt-get install -y "${faltando[@]}"
    fi
}

# Ubuntu/Debian: instala automaticamente as dependencias que estiverem faltando.
if command -v apt-get >/dev/null 2>&1 && command -v dpkg-query >/dev/null 2>&1; then
    instalar_dependencias_debian
fi

if ! command -v cmake >/dev/null 2>&1; then
    echo "Erro: CMake nao encontrado."
    echo "Ubuntu/Debian: sudo apt install cmake build-essential libglut-dev libgl1-mesa-dev"
    exit 1
fi

if ! command -v c++ >/dev/null 2>&1 && ! command -v g++ >/dev/null 2>&1; then
    echo "Erro: compilador C++ nao encontrado."
    echo "Ubuntu/Debian: sudo apt install build-essential"
    exit 1
fi

if [[ ! -f /usr/include/GL/freeglut.h && ! -f /usr/include/GL/glut.h ]]; then
    echo "Erro: cabecalhos do GLUT/FreeGLUT nao encontrados."
    echo "Ubuntu/Debian: sudo apt install libglut-dev libgl1-mesa-dev"
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
