# Computacao Grafica

Trabalho universitario de Computacao Grafica desenvolvido em C++ com OpenGL e FreeGLUT.

O projeto pode ser aberto e compilado normalmente pelo VS Code no Windows e no Linux usando CMake. A solucao do Visual Studio continua disponivel para quem preferir usa-la.

## Execucao rapida

Foram adicionados scripts que configuram o CMake, compilam e executam o projeto automaticamente.

### Linux - Ubuntu/Debian

Basta executar:

```bash
./run.sh
```

O script verifica e instala automaticamente, quando necessario, as dependencias:

- `cmake`
- `build-essential`
- `libglut-dev`
- `libgl1-mesa-dev`

Se preferir instalar manualmente:

```bash
sudo apt update
sudo apt install cmake build-essential libglut-dev libgl1-mesa-dev
```

Depois, execute novamente:

```bash
./run.sh
```

O `run.sh` ja esta marcado como executavel no repositorio. Se o sistema remover essa permissao por algum motivo, tambem pode ser executado com:

```bash
bash run.sh
```

### Windows

Instale:

- CMake disponivel no `PATH`;
- Visual Studio Build Tools 2019/2022 ou Visual Studio com a carga de trabalho **Desenvolvimento para Desktop com C++**.

Depois, na raiz do projeto, execute:

```bat
run.bat
```

Tambem e possivel dar duplo clique em `run.bat` pelo Explorador de Arquivos.

Os dois scripts geram os arquivos em `build/` e executam o binario em `build/bin/`.

## VS Code

Ao abrir a pasta do projeto no VS Code, instale as extensoes recomendadas pelo workspace:

- C/C++ (`ms-vscode.cpptools`)
- CMake Tools (`ms-vscode.cmake-tools`)

O CMake Tools configura o IntelliSense, a compilacao e a depuracao a partir do `CMakeLists.txt` da raiz.

### Linux

1. Clone o repositorio e abra a pasta raiz no VS Code.
2. Quando o CMake Tools pedir um Kit, selecione o GCC/G++ instalado no sistema.
3. Execute `CMake: Configure`.
4. Execute `CMake: Build`.
5. Use `CMake: Run Without Debugging` para executar ou `CMake: Debug` para depurar.

Tambem e possivel compilar pelo terminal:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/bin/ComputacaoGrafica
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

Pelo terminal:

```powershell
cmake -S . -B build
cmake --build build --config Debug
.\build\bin\ComputacaoGrafica.exe
```

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
├── run.sh
├── run.bat
├── ComputacaoGrafica.sln
├── ComputacaoGrafica/
│   ├── ComputacaoGrafica.cpp
│   └── freeglut/
└── .vscode/
    ├── extensions.json
    └── settings.json
```

Os arquivos gerados pela compilacao ficam fora do controle de versao por meio do `.gitignore`.
