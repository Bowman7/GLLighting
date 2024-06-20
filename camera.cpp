#include"camera.hpp"

Camera::Camera(){
  cameraPos = glm::vec3(0.0f,0.0f,3.0f);
  cameraFront = glm::vec3(0.0f,0.0f,-1.0f);
  cameraUp = glm::vec3(0.0f,1.0f,0.0f);  
  
  
}

Camera::~Camera(){
  
}
//update cam front and fov for scroll and mouse_callback
void Camera::UpdateCameraFront(glm::vec3 camFront,float fv){
  cameraFront = camFront;
  fov = fv;
  look = glm::lookAt(cameraPos,cameraPos+cameraFront,cameraUp);

  float currentFrame = glfwGetTime();
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;
}
glm::mat4  Camera::GetViewMatrix(){
  return look;
}

//handle input
void Camera::HandleInput(int val){
  cameraSpeed = 2.5f *deltaTime;
  switch(val){
  case 1:
    cameraPos += cameraFront*cameraSpeed;
    //std::cout<<"upe"<<std::endl;
    break;
  case 2:
    cameraPos -= cameraFront*cameraSpeed;
    //std::cout<<"down"<<std::endl;
    break;
  case 3:
    cameraPos -=glm::normalize(glm::cross(cameraFront,cameraUp))*cameraSpeed;
    break;
  case 4:
    cameraPos += glm::normalize(glm::cross(cameraFront,cameraUp))*cameraSpeed;
    break;
  default:
    break;
  }
  look = glm::lookAt(cameraPos,cameraPos+cameraFront,cameraUp);
  
  //cameraPos.y = 4.0f;
}
