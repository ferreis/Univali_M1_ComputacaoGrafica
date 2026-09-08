# Computacao Grafica

Trabalho universitario de Computacao Grafica desenvolvido em C++ com OpenGL e FreeGLUT.

O projeto pode ser aberto e compilado normalmente pelo VS Code no Windows e no Linux usando CMake. A solucao do Visual Studio continua disponivel para quem preferir usa-la.

## VS Code

Ao abrir a pasta do projeto no VS Code, instale as extensoes recomendadas pelo workspace:

- C/C++ (`ms-vscode.cpptools`)
- CMake Tools (`ms-vscode.cmake-tools`)

O CMake Tools configura o IntelliSense, a compilacao e a depuracao a partir do `CMakeLists.txt` da raiz.

### Linux - Ubuntu/Debian

Instale as dependencias:

```bash
sudo apt update
sudo apt install build-essential cmake freeglut3-dev libgl1-mesa-dev
```

Depois:

1. Clone o repositorio e abra a pasta raiz no VS Code.
2. Quando o CMake Tools pedir um Kit, selecione o GCC/G++ instalado no sistema.
3. Execute `CMake: Configure`.
4. Execute `CMake: Build`.
5. Use `CMake: Run Without Debugging` para executar ou `CMake: Debug` para depurar.

Tambem e possivel compilar pelo terminal:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/ComputacaoGrafica
```

### Windows

Requisitos:

- VS Code
- CMake disponivel no `PATH`
- Visual Studio Build Tools 2019/2022 ou Visual Studio com a carga de trabalho **Desenvolvimento para Desktop com C++**

A dependencia FreeGLUT para Windows ja esta incluida em `ComputacaoGrafica/freeglut`. O CMake seleciona automaticamente a biblioteca correta para x64/x86 e copia `freeglut.dll` para a pasta do executavel apos a compilacao.

Depois:

1. Clone o repositorio e abra a pasta raiz no VS Code.
2. No CMake Tools, selecione um Kit MSVC/Visual Studio instalado.
3. Execute `CMake: Configure`.
4. Execute `CMake: Build`.
5. Use `CMake: Run Without Debugging` para executar ou `CMake: Debug` para depurar.

Pelo terminal do Developer PowerShell/Prompt do Visual Studio:

```powershell
cmake -S . -B build
cmake --build build --config Debug
.\build\Debug\ComputacaoGrafica.exe
```

Dependendo do gerador escolhido pelo CMake, o executavel pode ficar diretamente em `build` em vez de `build\Debug`.

## Visual Studio

A configuracao original tambem continua disponivel:

1. Abra `ComputacaoGrafica.sln` no Visual Studio.
2. Selecione `Debug` e `x64`.
3. Compile e execute o projeto `ComputacaoGrafica`.

## Controles atuais

- Setas direcionais: movimentam o poligono quando a funcao estiver implementada.
- Barra de espaco: aplica escala quando a funcao estiver implementada.
- `Esc`: encerra a aplicacao.

## Estrutura relevante

```text
.
├── CMakeLists.txt
├── ComputacaoGrafica.sln
├── ComputacaoGrafica/
│   ├── ComputacaoGrafica.cpp
│   └── freeglut/
└── .vscode/
    ├── extensions.json
    └── settings.json
```

Os arquivos gerados pela compilacao ficam fora do controle de versao por meio do `.gitignore`.
