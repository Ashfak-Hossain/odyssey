#ifndef GAME_H
#define GAME_H

class Game
{
public:
  void init();
  void update(float deltaTime);
  void render();
  void handleInput(unsigned char key, int x, int y);
};

#endif