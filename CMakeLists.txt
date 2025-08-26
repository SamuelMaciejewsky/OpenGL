cmake_minimum_required(VERSION 4.1.0)
project(OpenGL_Test VERSION 1.0.0)

# Find OpenGL and GLFW packages
find_package(OpenGL REQUIRED)
find_package(glfw3 3.4 REQUIRED)

# Add the executable
add_executable(OpenGL_Test main.cc)

# If you have a Dependencies folder that contains GLFW as a subdirectory, use this
add_subdirectory(Dependencies/include)
add_subdirectory(Dependencies/lib-mingw-w64)