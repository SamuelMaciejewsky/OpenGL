#!/bin/bash
# ./run.sh on git bash

# Output File Name
OUTPUT="OpenGL_Test.exe"

mkdir -p build

# Path to Include and Lib
INCLUDE_PATH="./Dependencies/include/GLFW"
MINGW_LIB_PATH="./Dependencies/lib-mingw-w64"

# Source code
SRC_FILE="./src/main.cc"

echo "Compilando o código com os seguintes parâmetros:"
echo "INCLUDE_PATH: $INCLUDE_PATH"
echo "MINGW_LIB_PATH: $MINGW_LIB_PATH"
echo "SRC_FILE: $SRC_FILE"

# Compile command
g++ -I$INCLUDE_PATH -L$MINGW_LIB_PATH -lglfw3 -lopengl32 -lgdi32 -luser32 -lkernel32 $SRC_FILE -o build/$OUTPUT -D GLFW_DLL

# Check Compile
if [ $? -ne 0 ]; then
    echo "Erro na compilação"
    tail -n 20 build/$OUTPUT.log  # Mostra as últimas 20 linhas do arquivo de log de erro
    exit 1
else
    echo "Compilação bem-sucedida"
fi

# Copy DLL to build directory
cp $LIB_PATH//glfw3.dll ./build/