#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <myLib/logcomponent.h>

LogComponent::LogComponent() {}

LogComponent::~LogComponent() {}

void LogComponent::checkProgramInfoLog(unsigned int logObject, int size, char* infoLog, int success) {

    if (!success) {
        glGetProgramInfoLog(logObject, size, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

}

void LogComponent::checkVertexInfoLog(unsigned int logObject, int size, char* infoLog, int success) {

    if (!success) {
        glGetShaderInfoLog(logObject, size, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

}

void LogComponent::checkFragmentInfoLog(unsigned int logObject, int size, char* infoLog, int success) {

    if (!success) {
        glGetShaderInfoLog(logObject, size, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

}