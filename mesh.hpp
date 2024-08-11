#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<vector>

#include"math.h"


#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

#include"shader.hpp"

struct Vertex{
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;
};

struct Texture{
  unsigned int id;
  std::string type;
  std::string path;
};

//main class
class Mesh{
public:
  //mesh data
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;
  
  Mesh(std::vector<Vertex> vertices,
       std::vector<unsigned int> indices,
       std::vector<Texture> textures);

  void Draw(unsigned int ID);
  
  void setInt(const std::string &name, int value,unsigned int ID) const
  { 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
  }
  void setFloat(const std::string &name, float value,unsigned int ID) const
  { 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
  }
  void setMat4(const std::string &name, const glm::mat4 &mat,unsigned int ID) const
  {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }

  void setVec3(const std::string &name, float x, float y, float z,unsigned int ID) const
  { 
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
  }
  void Update(glm::mat4 look,glm::vec3 cpos){
    lookMat = look;
    camPos = cpos;
  }
private:
  glm::vec3 lightPos = {1.0f,2.0f,1.5f};
  glm::mat4 lookMat;
  glm::vec3 camPos;
  //render data
  unsigned int VAO,VBO,EBO;
  void setupMesh();
  
};

