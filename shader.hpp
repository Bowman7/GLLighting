#pragma once

#include<glad/glad.h>
#include<iostream>
#include<fstream>
#include<sstream>

class Shader{
public:
  Shader();
  ~Shader();
  void Init(const char*,const char*);
  unsigned int GetID(){
    return shaderProgram;
  }
private:

  std::ifstream my_file;
  std::string vertexCode;
  std::string fragmentCode;
  const char* vcode;
  const char* fcode;
  std::stringstream vstream;
  std::stringstream fstream;
  
  
  unsigned int vertexShader;
  unsigned int fragmentShader;
  unsigned int shaderProgram;

  
};


