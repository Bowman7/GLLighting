#include "snake.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

Snake::Snake(){
  
  //buffers
  glGenVertexArrays(1,&VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1,&EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

  glGenBuffers(1,&VBO);
  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(vertice),vertice,GL_STATIC_DRAW);
   //for accessing
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);
  //for tex
  glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
  glEnableVertexAttribArray(2);

  //load texture
  container = loadTexture("Textures/container2.png");
  container_specular = loadTexture("Textures/container2_specular.png");
  
 
  
  //for light
  glGenVertexArrays(1,&l_VAO);
  glBindVertexArray(l_VAO);

  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  //attrib ptr
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0);

}
Snake::~Snake(){

}
//;load texture
unsigned int Snake::loadTexture(const char* location){
  //texture for cube
  unsigned int texture;
  glGenTextures(1,&texture);
  glBindTexture(GL_TEXTURE_2D,texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width,height,nrChannels;
  unsigned char* data = stbi_load(reinterpret_cast<const char*>(location),&width,&height,&nrChannels,0);
  if(data){
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else{
    std::cout<<"Failed to load texture"<<std::endl;
  }
  stbi_image_free(data);

  return texture;
}
void Snake::SetID(unsigned int id){
  ID = id;
  
}

void Snake::Update(glm::mat4 look,glm::vec3 cpos,glm::vec3 cFront){
  lookMat = look;
  camPos = cpos;
  camFront = cFront;
  
  
 
}
void Snake::Draw(){
  
  //for cube
  glUseProgram(ID);
  //liht color
  glm::vec3 ObjColor = glm::vec3(1.0f,0.5f,0.31f);
  setVec3("ObjectColor",ObjColor,ID);
  //setVec3("LightColor",1.0f,1.0f,1.0f,ID);
  //set lightpos
  //std::cout<<"light pos: "<<lightPos.x<<lightPos.y<<lightPos.z<<std::endl;
  setVec3("lightPos",lightPos.x,lightPos.y,lightPos.z,ID);
 
  //set material props
  setInt("material.diffuse",0,ID);
  setInt("material.specular",1,ID);
  
  //set view pos
  setVec3("viewPos",viewPos,ID);
  setFloat("material.shininess",32.0f,ID);

  //for light material
  //change acolor
  /*glm::vec3 lightColor;
  lightColor.x = sin(glfwGetTime()*2.0f);
  lightColor.y = sin(glfwGetTime()*0.7f);
  lightColor.z = sin(glfwGetTime()*1.3f);

  glm::vec3 diffuseColor = lightColor *glm::vec3(0.5f);
  glm::vec3 ambientColor = diffuseColor *glm::vec3(0.2f);
  
  setVec3("light.ambient",ambientColor.x,ambientColor.y,ambientColor.z,ID);
  setVec3("light.diffuse",diffuseColor.x,diffuseColor.y,diffuseColor.z,ID);
  setVec3("light.specular",1.0f,1.0f,1.0f,ID);
  */
  //FOR DIRLIGHT STRUCT
  setVec3("dirLight.direction",-0.2f,-1.0f,-0.3f,ID);
  setVec3("dirLight.ambient" ,0.05f, 0.05f, 0.05f,ID);
  setVec3("dirLight.diffuse" ,0.4f, 0.4f, 0.4f,ID);
  setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f,ID);

  //FOR POINTLIGHT STRUCT
  //pointlight 1
  setVec3("pointLights[0].position",pointLightPositions[0],ID);
  setVec3("pointLights[0].ambient" ,1.0f, 0.0f, 0.0f,ID);
  setVec3("pointLights[0].diffuse" ,0.8f, 0.8f, 0.8f,ID);
  setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f,ID);
  setFloat("pointLights[0].constant",1.0f,ID);
  setFloat("pointLights[0].linear",0.09f,ID);
  setFloat("pointLights[0].quadratic",0.032f,ID);

  //point light 2
  setVec3("pointLights[1].position",pointLightPositions[1],ID);
  setVec3("pointLights[1].ambient" ,0.0f, 1.0f, 0.0f,ID);
  setVec3("pointLights[1].diffuse" ,0.8f, 0.8f, 0.8f,ID);
  setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f,ID);
  setFloat("pointLights[1].constant",1.0f,ID);
  setFloat("pointLights[1].linear",0.09f,ID);
  setFloat("pointLights[1].quadratic",0.032f,ID);

  //point light 3
  setVec3("pointLights[2].position",pointLightPositions[2],ID);
  setVec3("pointLights[2].ambient" ,0.0f, 0.0f, 1.0f,ID);
  setVec3("pointLights[2].diffuse" ,0.8f, 0.8f, 0.8f,ID);
  setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f,ID);
  setFloat("pointLights[2].constant",1.0f,ID);
  setFloat("pointLights[2].linear",0.09f,ID);
  setFloat("pointLights[2].quadratic",0.032f,ID);

  //point light 4
  setVec3("pointLights[3].position",pointLightPositions[3],ID);
  setVec3("pointLights[3].ambient" ,0.05f, 0.05f, 0.05f,ID);
  setVec3("pointLights[3].diffuse" ,0.8f, 0.8f, 0.8f,ID);
  setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f,ID);
  setFloat("pointLights[3].constant",1.0f,ID);
  setFloat("pointLights[3].linear",0.09f,ID);
  setFloat("pointLights[3].quadratic",0.032f,ID);

  //FOR SPOTLIGHT STRUCT
  setVec3("spotLight.position",camPos.x,camPos.y,camPos.z,ID);
  setVec3("spotLight.direction",camFront.x,camFront.y,camFront.z,ID);
  setVec3 ("spotLight.ambient" ,0.0f, 0.0f, 0.0f,ID);
  setVec3 ("spotLight.diffuse" ,1.0f, 1.0f, 1.0f,ID);
  setVec3 ("spotLight.specular", 1.0f, 1.0f, 1.0f,ID);
  setFloat("spotLight.constant",1.0f,ID);
  setFloat("spotLight.linear",0.09f,ID);
  setFloat("spotLight.quadratic",0.032f,ID);
  setFloat("spotLight.cutOff",glm::cos(glm::radians(12.5f)),ID);
  setFloat("spotLight.outerCutOff",glm::cos(glm::radians(15.0f)),ID);

  //proj
  glm::mat4 projection =  glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
  glm::mat4 view = lookMat;
  setMat4("proj",projection,ID);
  setMat4("view",view,ID);

  glm::mat4 model = glm::mat4(1.0f);
  setMat4("model",model,ID);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D,container);
  
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D,container_specular);
  
  glBindVertexArray(VAO); 
  //draw
  for(unsigned int i=0;i<10;i++){
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model,cubePositions[i]);
    float angle = 20.0f*i;
    model = glm::rotate(model,glm::radians(angle),glm::vec3(1.0f,0.3f,0.5f));
    setMat4("model",model,ID);

    glm::mat4 inverseModel = glm::inverse(model);
    setMat4("inverseModel",inverseModel,ID);
  
    
    glDrawArrays(GL_TRIANGLES,0,36);
  }
  
  //for light
  glUseProgram(l_ID);
  setMat4("proj",projection,l_ID);
  setMat4("view",view,l_ID);

  glBindVertexArray(l_VAO);
  for(unsigned int i=0;i<4;i++){
    model = glm::mat4(1.0f);
    model = glm::translate(model,pointLightPositions[i]);
    model = glm::scale(model,glm::vec3(0.2f));
    setMat4("model",model,l_ID);

    glDrawArrays(GL_TRIANGLES,0,36);
  }


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
  pointLightPositions[2] -=glm::vec3(0.0f,0.0f,1.0f);
}
void Snake::moveSouth(){
  pointLightPositions[2] +=glm::vec3(0.0f,0.0f,1.0f);
}
void Snake::moveEast(){
  pointLightPositions[2] +=glm::vec3(1.0f,0.0f,0.0f);
}
void Snake::moveWest(){
  pointLightPositions[2] -=glm::vec3(1.0f,0.0f,0.0f);
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
