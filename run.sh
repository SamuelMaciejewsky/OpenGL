#!/bin/bash
# ./run.sh on git bash

# Output File Name
OUTPUT="OpenGL_Test.exe"

# Path to Include and Lib
INCLUDE_PATH=".\\Dependencies\\GLFW\\include"
LIB_PATH=".\\Dependencies\\GLFW\\lib-vc2022"

# Libs to link
LIBS="-lglfw3 -lOpenGL32"

# Source code
SRC_FILES=".\\src\\main.cc"

# Compile command
g++ $SRC_FILES -o build\\$OUTPUT -I$INCLUDE_PATH -L$LIB_PATH $LIBS

# Check Compile
if [ $? -eq 0 ]; then
    echo "Compilado com sucesso"
else 
    echo "Erro na compilação"
    exit 1
fi

# Copy DLL to build directory
cp $LIB_PATH\\glfw3.dll .\\build\\