#include"shader.hpp"

Shader::Shader(){

}

Shader::~Shader(){

}

void Shader::Init(const char* vsource,const char* fsource){
  //for vertex shader
  
  my_file.open(vsource);
  if(!my_file.is_open()){
    std::cout<<"Error opening file"<<std::endl;
  }
  vstream<<my_file.rdbuf();
  my_file.close();
  vertexCode = vstream.str();
  vcode = vertexCode.c_str();
  
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader,1,&vcode,NULL);
  glCompileShader(vertexShader);

  //check
  int  success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success){
     glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
     std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  
  //for fragment shader
  my_file.open(fsource);
  
  if(!my_file.is_open()){
    std::cout<<"Error opening file"<<std::endl;
  }
  fstream<<my_file.rdbuf();
  my_file.close();
  fragmentCode = fstream.str();
  fcode = fragmentCode.c_str();
  
  fragmentShader  = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader,1,&fcode,NULL);
  glCompileShader(fragmentShader);
  
  //check
   glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if(!success){
     glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
     std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  
   //shader obj creation
  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram,vertexShader);
  glAttachShader(shaderProgram,fragmentShader);
  glLinkProgram(shaderProgram);

  glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
  if(!success){
     glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
     std::cout << "ERROR::LINK::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  //del sahder
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}
