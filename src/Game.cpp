#include "Platform.h"
#include "Game.h"

void Game::init()
{
  glClearColor(0, 0.5, 1, 1);
}

void Game::update(float deltaTime) {}

void Game::render()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glutSwapBuffers();
}

void Game::handleInput(unsigned char key, int x, int y) {}