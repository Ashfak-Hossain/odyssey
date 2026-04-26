#ifndef GAME_H
#define GAME_H

#include <vector>

#include "Camera.h"
#include "InputManager.h"
#include "Level.h"
#include "Physics.h"
#include "Player.h"
#include "Tile.h"

class Game {
  Player       player;
  Camera       camera;
  Level        level;
  InputManager input;
  Physics      physics;

 public:
  Game();
  void init();
  void update(float deltaTime);
  void render();
  void handleKeyUp(unsigned char key, int x, int y);
  void handleKeyDown(unsigned char key, int x, int y);
};

#endif  // GAME_H