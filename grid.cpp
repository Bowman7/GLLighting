#include"grid.hpp"

Grid::Grid(){
  glGenVertexArrays(1,&VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1,&VBO);
  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(grid_vertex),grid_vertex,GL_STATIC_DRAW);
  //for accessing
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0);
 
}

Grid::~Grid(){

}

void Grid::Update(){
  view = glm::mat4(1.0f);
  view = glm::translate(view,glm::vec3(0.0f,0.0f,-4.0f));
  view = glm::rotate(view,glm::radians(90.0f),glm::vec3(1.0f,0.0f,0.0f));
  unsigned int viewLoc = glGetUniformLocation(ID,"view");
  glUniformMatrix4fv(viewLoc,1,GL_FALSE,glm::value_ptr(view));
  
}

void Grid::Draw(){
  glUseProgram(ID);

  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES,0,6);
  glBindVertexArray(0);
}
