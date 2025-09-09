#ifndef LOGCOMPONENT_H
#define LOGCOMPONENT_H

#pragma once

class LogComponent {

 private:

   int success, size;
   char infoLog[512];
   unsigned int logObject;

 public:

   void checkProgramInfoLog(unsigned int logObject, int size, char* infoLog, int success);
   void checkVertexInfoLog(unsigned int logObject, int size, char* infoLog, int success);
   void checkFragmentInfoLog(unsigned int logObject, int size, char* infoLog, int success);
   
   LogComponent();
   ~LogComponent();

};

#endif