#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "logcomponent.h"

LogComponent::LogComponent()
{

}

LogComponent::~LogComponent()
{

}

void LogComponent::checkProgramInfoLog(unsigned int logObject, int size, char* infoLog) {

    if (!success) {
        glGetProgramInfoLog(logObject, size, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

}

void LogComponent::checkShaderInfoLog(unsigned int logObject, int size, char* infoLog) {

    if (!success) {
        glGetShaderInfoLog(logObject, size, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::LINKING_FAILED\n" << infoLog << std::endl;
    }

}