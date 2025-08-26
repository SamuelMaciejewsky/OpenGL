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
g++ -I$INCLUDE_PATH --verbose -static $SRC_FILE -o build/$OUTPUT -L$MINGW_LIB_PATH -D GLFW_DLL -lglfw3 -lgdi32 -luser32 -lkernel32 -lopengl32 -llibglfw3dll -lglu32

EXIT_STATUS=$?

# Check Compile
if [ $EXIT_STATUS -ne 0 ]; then
    echo "Compile error, Exit code: $EXIT_STATUS"
    exit $EXIT_STATUS
else
    echo "Compilation Successfully!"
fi
