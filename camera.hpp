#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

class Camera{

public:
  Camera();
  ~Camera();
  void HandleInput(int val);
  void UpdateCameraFront(glm::vec3,float);
  glm::mat4 GetViewMatrix();
  glm::vec3 GetPos(){
    return cameraPos;
		       
  }
  glm::vec3 GetFront(){
    return cameraFront;
  }
private:
  glm::mat4 look;
  float fov = 45.0f;
  glm::vec3 cameraPos;
  glm::vec3 cameraFront;
  glm::vec3 cameraUp;
  glm::mat4 view ;
  glm::mat4 proj ;
  glm::mat4 model;
  //delta stuff
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  float cameraSpeed = 0.05f;

};
