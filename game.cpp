#include"game.hpp"

Game::Game(){
  snakeShader.Init("snake_shader.vert","snake_shader_spotlight.frag");
  lightShader.Init("snake_shader.vert","light_shader.frag");
  
  snake.SetID(snakeShader.GetID());
  snake.l_SetID(lightShader.GetID());

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
  snake.Update(camera.GetViewMatrix(),camera.GetPos(),camera.GetFront());
  snake.setView(camera.GetPos());
}

//draw
void Game::Draw(){
  //draw snake
  snake.Draw();
}

