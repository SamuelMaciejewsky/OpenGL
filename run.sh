#!/bin/bash
# ./run.sh on git bash

# Output File Name
OUTPUT="OpenGL_Test.exe"

mkdir -p build

# Path to Include and Lib
INCLUDE_PATH="./Dependencies/include"
MINGW_LIB_PATH="./Dependencies/lib-mingw-w64"

# Source code
SRC_FILE="./src/main.cc"

# Compile command
g++ -I$INCLUDE_PATH -L$MINGW_LIB_PATH -lglfw3 -llibglfw3dll -lopengl32 -lgdi32 -luser32 -lkernel32 $SRC_FILE -o build/$OUTPUT -D GLFW_DLL

EXIT_STATUS=$?

# Check Compile
if [ $EXIT_STATUS -ne 0 ]; then
    echo "Compile error, Exit code: $EXIT_STATUS"
    exit $EXIT_STATUS
else
    echo "Compilation Successfully!"
fi
# Copy DLL to build directory
cp $LIB_PATH//glfw3.dll ./build/