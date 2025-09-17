#ifndef SHADER_H
#define SHADER_H

#pragma once

#include <glad/glad.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Shader {

 private:

  void checkShadersCompileErrors(unsigned int shader, std::string type);
  void checkProgramLinkErrors(unsigned int program, std::string type);

 public:

  unsigned int ID;

  // Use/active the shader
  void use();

  // Utility uniform functions
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;

  // Constructor and destructor
  Shader(const char* vertexShader, const char* fragmentShader);
  ~Shader();

};

Shader::Shader(const char* vertexShader, const char* fragmentShader) {

  // 1. Retrieve the vertex/fragment source code from filePath
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  // Ensure ifstream objects can throw exceptions
  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {

    // Open files
    vShaderFile.open(reinterpret_cast<const char*>(vertexShader));
    fShaderFile.open(reinterpret_cast<const char*>(fragmentShader));
    std::stringstream vShaderStream, fShaderStream;

    // Read file's buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    // Close file handlers
    vShaderFile.close();
    fShaderFile.close();

    // Convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();

  } catch (std::ifstream::failure& e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
  }

  const char* vShaderCode = vertexCode.c_str();
  const char* fShaderCode = fragmentCode.c_str();


  // 2. Compile shaders
  unsigned int vertex, fragment;

  // vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);

  // Print compile errors if any
  checkShadersCompileErrors(vertex, "VERTEX");

  // fragment shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);

  // print compile errors if any
  checkShadersCompileErrors(fragment, "FRAGMENT");

  // shader program
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);

  // print linking errors if any
  checkProgramLinkErrors(ID, "PROGRAM");

  // delete the shaders as they're linked into our program now and no longer necessary
  glDeleteShader(vertex);
  glDeleteShader(fragment);

}

Shader::~Shader() {
  glDeleteProgram(ID);
}

void Shader::use() {
  glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::checkShadersCompileErrors(unsigned int shader, std::string type) {

  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (!success) {

    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
  
  }

}

void Shader::checkProgramLinkErrors(unsigned int program, std::string type) {

  int success;
  char infoLog[512];
  glGetProgramiv(program, GL_LINK_STATUS, &success);

  if (!success) {

    glGetProgramInfoLog(program, 512, NULL, infoLog);
    std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
  
  }

}

#endif