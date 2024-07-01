#include "snake.hpp"

Snake::Snake(){
  
  //buffers
  glGenVertexArrays(1,&VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1,&EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

  glGenBuffers(1,&VBO);
  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
   //for accessing
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);
  

  //for light
  glGenVertexArrays(1,&l_VAO);
  glBindVertexArray(l_VAO);

  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  //attrib ptr
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0);

}

Snake::~Snake(){

}

void Snake::SetID(unsigned int id){
  ID = id;
  
}

void Snake::Update(glm::mat4 look){
  lookMat = look;
  
  
 
}
void Snake::Draw(){
  
  //for cube
  glUseProgram(ID);
  //liht color
  glm::vec3 ObjColor = glm::vec3(1.0f,0.5f,0.31f);
  setVec3("ObjectColor",ObjColor.x,ObjColor.y,ObjColor.z,ID);
  setVec3("LightColor",1.0f,1.0f,1.0f,ID);
  //set lightpos
  //std::cout<<"light pos: "<<lightPos.x<<lightPos.y<<lightPos.z<<std::endl;
  setVec3("lightPos",lightPos.x,lightPos.y,lightPos.z,ID);
  //set view pos
  setVec3("ViewPos",viewPos.x,viewPos.y,viewPos.z,ID);
  //proj
  glm::mat4 projection =  glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
  glm::mat4 view = lookMat;
  setMat4("proj",projection,ID);
  setMat4("view",view,ID);
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model,snake_pos[3]);
  setMat4("model",model,ID);

  glm::mat4 inverseModel = glm::inverse(model);
  setMat4("inverseModel",inverseModel,ID);

  //set material props
  setVec3("material.ambient",1.0f,0.5f,0.31f,ID);
  setVec3("material.diffuse",1.0f,0.5f,0.31f,ID);
  setVec3("material.specular",0.5f,0.5f,0.5f,ID);
  setFloat("material.shininess",32.0f,ID);
  //for light material
  //change acolor
  glm::vec3 lightColor;
  lightColor.x = sin(glfwGetTime()*2.0f);
  lightColor.y = sin(glfwGetTime()*0.7f);
  lightColor.z = sin(glfwGetTime()*1.3f);

  glm::vec3 diffuseColor = lightColor *glm::vec3(0.5f);
  glm::vec3 ambientColor = diffuseColor *glm::vec3(0.2f);
  
  setVec3("light.ambient",ambientColor.x,ambientColor.y,ambientColor.z,ID);
  setVec3("light.diffuse",diffuseColor.x,diffuseColor.y,diffuseColor.z,ID);
  setVec3("light.specular",1.0f,1.0f,1.0f,ID);
  
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES,0,36);
  
  
  //for light
  glUseProgram(l_ID);
  glm::mat4 l_model = glm::mat4(1.0f);
  l_model = glm::translate(l_model,lightPos);
  l_model = glm::scale(l_model,glm::vec3(0.2f));
  
  setMat4("model",l_model,l_ID);
  setMat4("proj",projection,l_ID);
  setMat4("view",view,l_ID);
  
  glBindVertexArray(l_VAO);
  glDrawArrays(GL_TRIANGLES,0,36);
  //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
  //glBindVertexArray(0);
}
//event triggered
bool Snake::EventTriggered(double interval){
  double currentTime = (double)glfwGetTime();
  if(currentTime-lastUpdatedTime >=interval){
    lastUpdatedTime = currentTime;
    return true;
  }
  return false;
}
//handle input

void Snake::moveNorth(){
  lightPos -=glm::vec3(0.0f,0.0f,1.0f);
}
void Snake::moveSouth(){
  lightPos +=glm::vec3(0.0f,0.0f,1.0f);
}
void Snake::moveEast(){
  lightPos +=glm::vec3(1.0f,0.0f,0.0f);
}
void Snake::moveWest(){
  lightPos -=glm::vec3(1.0f,0.0f,0.0f);
}
void Snake::HandleInput(int val){
  switch(val){
  case 6:
    moveNorth();
    break;
  case 7:
    moveSouth();
    break;
  case 8:
    moveWest();
    break;
  case 9:
    moveEast();
    break;
  default:
    break;
    
  }
}
