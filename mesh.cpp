#include"mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices,
	   std::vector<unsigned int> indices,
	   std::vector<Texture> textures){

  this->vertices = vertices;
  this->indices = indices;
  this->textures = textures;

  setupMesh();
}

//setup
void Mesh::setupMesh(){

  glGenVertexArrays(1,&VAO);
  glGenBuffers(1,&VBO);
  glGenBuffers(1,&EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER,VBO);

  glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(Vertex),&vertices[0],GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(unsigned int),&indices[0],GL_STATIC_DRAW);

  //vertex positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)0);
  
  //vertex normals
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,Normal));
 
  //tex coordinates
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,TexCoords));
  

  glBindVertexArray(0);
 
}

//draw
void Mesh::Draw(unsigned int ID){

  glUseProgram(ID);
  
  unsigned int diffuseNr = 1;
  unsigned int specularNr = 1;
  for(unsigned int i=0;i<textures.size();i++){
    glActiveTexture(GL_TEXTURE0+i);
    //retrieve tex number
    std::string number;
    std::string name = textures[i].type;
    if(name == "texture_diffuse"){
      number =std::to_string(diffuseNr++);
    }else if(name == "texture_specular"){
      number =std::to_string(specularNr++);
    }
    
    //setInt(("material."+name+number).c_str(),i,ID);
    glUniform1i(glGetUniformLocation(ID, (name + number).c_str()), i);
    glBindTexture(GL_TEXTURE_2D,textures[i].id);
  }

  glm::mat4 projection = glm::perspective(glm::radians(45.0f),1920.0f/1080.0f,0.1f, 100.0f);
  glm::mat4 view = lookMat;;

  setMat4("projection",projection,ID);
  setMat4("view",view,ID);

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
  model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
  setMat4("model", model,ID);
  
  
  
  //draw mesh
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES,
		 static_cast<unsigned int>(indices.size()),GL_UNSIGNED_INT,0);
  glBindVertexArray(0);

  glActiveTexture(GL_TEXTURE0);
}
