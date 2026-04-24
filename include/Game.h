#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game {
  Player player;
  bool   keyPressed[256];

 public:
  Game();
  void init();
  void update(float deltaTime);
  void render();
  void handleKeyUp(unsigned char key, int x, int y);
  void handleKeyDown(unsigned char key, int x, int y);
};

#endif