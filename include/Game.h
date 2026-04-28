#ifndef GAME_H
#define GAME_H

#include <vector>

#include "Camera.h"
#include "InputManager.h"
#include "Level.h"
#include "LevelManager.h"
#include "Physics.h"
#include "Player.h"
#include "Tile.h"

class Game {
  Level        level;
  Player       player;
  Camera       camera;
  Physics      physics;
  LevelManager levelManager;
  InputManager inputManager;

 public:
  Game();
  void init();
  void update(float deltaTime);
  void render();
  void handleKeyUp(unsigned char key, int x, int y);
  void handleKeyDown(unsigned char key, int x, int y);
};

#endif  // GAME_H