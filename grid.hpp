#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

#include"math.h"

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

class Grid{
public:
  Grid();
  ~Grid();
  void SetID(unsigned int id){
    ID =id;
  }
  void Update();
  void Draw();

private:
  glm::mat4 view;
  unsigned int VAO;
  unsigned int VBO;
  unsigned int ID;
  float grid_vertex[18]={
    0.3f, 0.3f, 0.0f,
    -0.3f, 0.3f, 0.0f,
    -0.3f, -0.3f, 0.0f,
    0.3f, 0.3f, 0.0f,
    -0.3f, -0.3f, 0.0f,
    0.3f, -0.3f, 0.0f
  };
};
