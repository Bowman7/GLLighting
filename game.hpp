#pragma once


#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<filesystem>

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

#include"grid.hpp"
#include"snake.hpp"
#include"shader.hpp"
#include"camera.hpp"

//loading model
#include"model.hpp"

class Game{
public:
  Game();
  ~Game();
  void Update(glm::vec3,float);
  void Draw();
  void HandleInput(int);
private:
  //for model loading
  Shader modelShader;
  
  Model ourModel;
  
  int ip;
  Shader gridShader;
  Shader snakeShader;
  Shader lightShader;
  Grid grid;
  Snake snake;
  Camera camera;
  
};
