#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<map>

#include"math.h"

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

//load model
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

//#include"stb_image.h"
#include"shader.hpp"
#include"mesh.hpp"



class Model{
public:
  //optimize
  std::vector<Texture> textures_loaded;  
  //model data
  std::vector<Mesh> meshes;
  std::string directory;
  
  Model();
  void Load(std::string );
  
  void SetID(unsigned int id){
    ID = id;
  }
  //draw model,and thus all its meshes
  void Draw();

  void setMat4(const std::string &name, const glm::mat4 &mat,unsigned int ID) const
  {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }

  void Update(glm::mat4);
private:
  
  //for shader id
  unsigned int ID;
  
  void loadModel(std::string const &path);
  void processNode(aiNode *node,const aiScene *scene);
  Mesh processMesh(aiMesh *mesh,const aiScene *scene);
  std::vector<Texture> loadMaterialTextures(aiMaterial *mat,aiTextureType type,
					    std::string typeName);

  unsigned int TextureFromFile(const char* path,const std::string &directory);
};