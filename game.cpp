#include"game.hpp"

Game::Game(){
  snakeShader.Init("snake_shader.vert","snake_multiple.frag");
  lightShader.Init("snake_shader.vert","light_shader.frag");

  
  
  snake.SetID(snakeShader.GetID());
  snake.l_SetID(lightShader.GetID());


  //model
  modelShader.Init("model_loading.vert","model_loading.frag");
  ourModel.SetID(modelShader.GetID());

  stbi_set_flip_vertically_on_load(true);
  ourModel.Load("backpack/backpack.obj");
  //ourModel.Load("Model/cottage/cottage_obj.obj");
  //ourModel.Load("Model/tree/lowpoly.obj");
  
}


Game::~Game(){

}

void Game::HandleInput(int val){
  snake.HandleInput(val);
  camera.HandleInput(val);
}
//update
void Game::Update(glm::vec3 camFront,float fv){
  //handle input
  camera.UpdateCameraFront(camFront,fv);
  
  ourModel.Update(camera.GetViewMatrix(),camera.GetPos());
  
  snake.Update(camera.GetViewMatrix(),camera.GetPos(),camera.GetFront());
  snake.setView(camera.GetPos());
}

//draw
void Game::Draw(){
  //draw snake
  //snake.Draw();
  //draw model
  ourModel.Draw();
}

