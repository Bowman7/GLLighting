#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

#include"math.h"

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

#include"shader.hpp"

class Snake{
public:
  Snake();
  ~Snake();
  void SetID(unsigned int id);
  void l_SetID(unsigned int id){
    l_ID = id;
  }
  void Update(glm::mat4);
  void Draw();
  void HandleInput(int);
  void moveNorth();
  void moveSouth();
  void moveEast();
  void moveWest();
  bool EventTriggered(double);
  void setMat4(const std::string &name, const glm::mat4 &mat,unsigned int id) const
  {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }
  void setVec3(const std::string &name, float x, float y, float z,unsigned int id) const
  { 
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z); 
  }
  void setFloat(const std::string &name, float value,unsigned int id) const
  { 
    glUniform1f(glGetUniformLocation(id, name.c_str()), value); 
  }
  void setInt(const std::string &name, int value,unsigned int id) const
  { 
    glUniform1i(glGetUniformLocation(id, name.c_str()), value); 
  }
  void setView(glm::vec3 pos){
    viewPos = pos;
  }

  unsigned int loadTexture(const  char*);
private:
  //glm::mat4 model = glm::mat4(1.0f);
  //glm::vec3 model_pos = glm::vec3(0.0f,0.0f,-3.0f);
  glm::vec3 lightPos =glm::vec3(0.0f,1.0f,0.0f);
  glm::vec3 viewPos;
  glm::mat4 lookMat;
  //int bodyCount = 3;
  double lastUpdatedTime = 0.0f;
  //vaos vbo ebo attrib pointers
  unsigned int VAO,p_VAO,l_VAO;
  unsigned int VBO,p_VBO,l_VBO;
  unsigned int EBO,l_EBO;
  unsigned int ID,l_ID;
  unsigned int container;
  unsigned int container_specular;

  //for plane
  float plane_vertex[18]={
    -0.8f,0.8f,0.0f,
    0.8f,0.8f,0.0f,
    -0.8f,-0.8f,0.0f,
    0.8f,0.8f,0.0f,
    -0.8f,-0.8f,0.0f,
    0.8f,-0.8f,0.0f
  };
  glm::vec3 snake_pos[4]={
    glm::vec3(0.0f,0.0f,-3.0f),
    glm::vec3(0.0f,0.0f,-4.0f),
    glm::vec3(0.0f,0.0f,-5.0f),
    glm::vec3(0.0f,0.0f,4.0f)
  };
  float vertex[24]={
    //pos                //colors       
   -0.5f,-0.5f,0.0f,   1.0f,0.3f,0.0f, 
   0.5f,-0.5f,0.0f,    0.5f,0.2f,0.0f, 
    -0.5f,0.5f,0.0f,     0.1f,0.0f,1.0f,
    0.5,0.5f,0.0f,       1.0f,1.0f,1.0f
  };
  float vertice[288] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};
  float vertices[216] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
  };
  float cube_vertex[256] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
				          
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f,0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f,0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f,0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,0.0f,
				          
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,0.0f,
				          
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f,0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f,0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f,0.0f,
				          
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,0.0f,
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f,0.0f,
     0.5f, -0.5f,  0.5f,   0.0f, 1.0f,0.0f,
     0.5f, -0.5f,  0.5f,   0.0f, 1.0f,0.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, 1.0f,0.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,0.0f,
				          
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,0.0f,
     0.5f,  0.5f, -0.5f,   0.0f, 1.0f,0.0f,
     0.5f,  0.5f,  0.5f,   0.0f, 1.0f,0.0f,
     0.5f,  0.5f,  0.5f,   0.0f, 1.0f,0.0f,
    -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,0.0f,
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,0.0f
  };
  unsigned int indices[6]={
    0,1,2,
    2,3,1
  };
    
};
