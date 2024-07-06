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
  glm::vec3 TexCoords;
};

sturct Texture{
  unsigned int id;
  string type;
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

  void Draw(Shader &shader);
private:
  //render data
  unsigned int VAO,VBO,EBO;
  void setupMesh();
  
};

