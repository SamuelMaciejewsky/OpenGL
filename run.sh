#!/bin/bash
# ./run.sh on git bash

# Output File Name
OUTPUT="OpenGL_Test.exe"

mkdir -p build

# Path to Include and Lib
INCLUDE_PATH="./Dependencies/include/"
MINGW_LIB_PATH="./Dependencies/lib-mingw-w64/"

# Source code
SRC_FILE="./src/main.cc"

# Compile command
g++ -I$INCLUDE_PATH -L$MINGW_LIB_PATH -lglfw3 -lopengl32 -lgdi32 -luser32 -lkernel32 $SRC_FILE -o build/$OUTPUT -D GLFW_DLL

# Check Compile
if [ $? -eq 0 ]; then
    echo "Compilado com sucesso"
else 
    echo "Erro na compilação"
    exit 1
fi

# Copy DLL to build directory
cp $LIB_PATH//glfw3.dll ./build/