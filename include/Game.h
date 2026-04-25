#ifndef GAME_H
#define GAME_H

#include <vector>

#include "Camera.h"
#include "Player.h"
#include "Tile.h"

class Game {
  Player player;
  Camera camera;
  bool   keyPressed[256];

  std::vector<Tile> tiles;

  void resolveCollisionX(Tile& tile);
  void resolveCollisionY(Tile& tile);

 public:
  Game();
  void init();
  void update(float deltaTime);
  void render();
  void handleKeyUp(unsigned char key, int x, int y);
  void handleKeyDown(unsigned char key, int x, int y);
};

#endif