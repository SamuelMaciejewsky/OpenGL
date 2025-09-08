#ifndef LOGCOMPONENT_H
#define LOGCOMPONENT_H

#pragma once

class LogComponent {

 public:

    int success, size;
    char infoLog[512];
    unsigned int logObject;

 private:

    void checkProgramInfoLog(unsigned int logObject, int size, char* infoLog);
    void checkShaderInfoLog(unsigned int logObject, int size, char* infoLog);

    LogComponent();
    ~LogComponent();

};

#endif