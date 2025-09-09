cmake_minimum_required(VERSION 4.1.0)
project(OpenGL_Test VERSION 1.0.0)

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake )

# Encontrar pacotes necessários
find_package( OpenGL REQUIRED )
find_package( glfw3 3.4 REQUIRED )
find_package( glad REQUIRED )
find_package( khr REQUIRED )

# Incluir diretórios para os cabeçalhos (glad.h)
include_directories(${CMAKE_SOURCE_DIR}/glad) 

# Criar o executável com main.cc e glad.c
add_executable( OpenGL_Test src/main.cc src/glad.c )

# Diretórios de inclusão adicionais
target_include_directories( OpenGL_Test PRIVATE Dependencies/include )

# Linkar com as bibliotecas necessárias
target_link_libraries( OpenGL_Test ${GLFW3_LIBRARY} OpenGL::GL )
target_link_libraries( OpenGL_Test ${GLAD_LIBRARY} OpenGL::GL )
target_link_libraries( OpenGL_Test ${KHR_LIBRARY} OpenGL::GL )
target_link_libraries( OpenGL_Test ${myLib_LIBRARY} OpenGL::GL )

