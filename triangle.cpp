#include"triangle.hpp"


#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

Triangle::Triangle(unsigned int id){
  ID = id;
  timeVal = glfwGetTime();
  greenVal = (sin(timeVal)/2.0f)+0.5f;
  
  //vboss
  glGenVertexArrays(1,&VAO);
  glBindVertexArray(VAO);

  //for EBO
  glGenBuffers(1,&EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
  glGenBuffers(1,&VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(cube_vertex),cube_vertex,GL_STATIC_DRAW);
  

  //for pos
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0);
  //for col
  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);
  //for tex
  glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
  glEnableVertexAttribArray(2);

  //for texture
 

  glGenTextures(1,&texture1);
  glBindTexture(GL_TEXTURE_2D,texture1);
  //warrping and filtering
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  stbi_set_flip_vertically_on_load(true);  
  data = stbi_load("Textures/container.jpg",&width,&height,&nrChannels,0);
  if(data){
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }else{
    std::cout<<"Failed to load texture 1"<<std::endl;
  }
  stbi_image_free(data);

  // for texture 2

  glGenTextures(1,&texture2);
  glBindTexture(GL_TEXTURE_2D,texture2);
  //warrping and filtering
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  stbi_set_flip_vertically_on_load(true);  
  data = stbi_load("Textures/walnut.png",&width,&height,&nrChannels,0);
  if(data){
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }else{
    std::cout<<"Failed to load texture 2"<<std::endl;
  }
  stbi_image_free(data);

  glUseProgram(ID);
  glUniform1i(glGetUniformLocation(ID,"Texture1"),0);
  glUniform1i(glGetUniformLocation(ID,"Texture2"),1);

  //to 3d
  //model
  model = glm::mat4(1.0f);
  model = glm::rotate(model,glm::radians(-55.0f),glm::vec3(1.0f,0.0f,0.0f));
  unsigned int modelLoc = glGetUniformLocation(ID,"model");
  glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));
  //view
  /*
  glm::mat4 view = glm::mat4(1.0f);
  view = glm::translate(view,glm::vec3(0.0f,0.0f,-3.0f));
  unsigned int viewLoc = glGetUniformLocation(ID,"view");
  glUniformMatrix4fv(viewLoc,1,GL_FALSE,glm::value_ptr(view));
  */
  //projection
  proj = glm::mat4(1.0f);
  proj = glm::perspective(glm::radians(fov),800.0f/600.0f,0.1f,100.0f);
  unsigned int projLoc = glGetUniformLocation(ID,"proj");
  glUniformMatrix4fv(projLoc,1,GL_FALSE,glm::value_ptr(proj));

  lastUpdatedTime = 0.0;



 
}

Triangle::~Triangle(){
  
}
//event triggered
bool Triangle::EventTriggered(double interval){
  double currentTime = (double)glfwGetTime();
  if(currentTime-lastUpdatedTime >= interval){
    lastUpdatedTime = currentTime;
    return true;
  }
  return false;
}
//update

void Triangle::Update(){
  //delta stuf
  
  timeVal = glfwGetTime();
  greenVal = (sin(timeVal)/2.0f)+0.5f;
  if(EventTriggered(0.3)){
    model = glm::rotate(model,(float)glfwGetTime()*glm::radians(50.0f),glm::vec3(1.0f,0.5f,0.0f));
    unsigned int modelLoc = glGetUniformLocation(ID,"model");
    glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));
  }

 
}

void Triangle::Draw(){
  //bind textures
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D,texture1);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D,texture2);
  
  glUseProgram(ID);

  vertexColorLocation = glGetUniformLocation(ID,"ourColor");
  glUniform4f(vertexColorLocation,0.0f,greenVal,0.0f,1.0f);

  
  glBindVertexArray(VAO);
  for(int i=0;i<10;i++){
    glm::mat4 model2 = glm::mat4(1.0f);
    model2 = glm::translate(model2,cubePositions[i]);
    float angle = 20.0f * i;
    model2 = glm::rotate(model2,glm::radians(angle),glm::vec3(1.0f,0.3f,0.5f));
    if(i%3 == 0){
      model2 = glm::rotate(model2,(float)glfwGetTime()*glm::radians(angle),glm::vec3(1.0f,1.0f,0.0f));
    }
    unsigned int model2Loc = glGetUniformLocation(ID,"model2");
    glUniformMatrix4fv(model2Loc,1,GL_FALSE,glm::value_ptr(model2));

    glDrawArrays(GL_TRIANGLES,0,36);
  }
  //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
  
  glBindVertexArray(0);

  
}
