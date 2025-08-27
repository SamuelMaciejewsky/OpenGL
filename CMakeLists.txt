cmake_minimum_required(VERSION 4.1.0)
project(OpenGL_Test VERSION 1.0.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.4 REQUIRED)

add_executable(OpenGL_Test src/main.cc)

target_include_directories(OpenGL_Test PRIVATE Dependencies/include)

target_link_libraries(OpenGL_Test ${GLFW3_LIBRARY} OpenGL::GL)