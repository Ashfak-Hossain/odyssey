#include "LevelManager.h"

#include <iostream>

#include "Config.h"

LevelManager ::LevelManager() : index(0), complete(false) {
  levelPaths = {
      "levels/level1.txt",
      "levels/level2.txt",
  };
}

void LevelManager::init(Player& player) {
  index    = 0;
  complete = false;
  loadCurrent(player);
}

void LevelManager::update(Player& player) {
  if (complete) {
    return;
  }
  if (!level.hasExit) {
    return;
  }

  Rect playerRect = player.getRect();

  if (playerRect.overlaps(level.exitDoor)) {
    index++;

    if (index >= (int)levelPaths.size()) {
      complete = true;
      std::cout << "[LevelManager] Game Complete! \n";
    } else {
      loadCurrent(player);
    }
  }
}

void LevelManager::loadCurrent(Player& player) {
  bool canLoad = level.load(levelPaths[index]);

  if (!canLoad) {
    std::cerr << "[LevelManager] failed to laod levels \n";
  }

  player.x        = level.playerStartX;
  player.y        = level.playerStartY;
  player.vx       = 0;
  player.vy       = 0;
  player.onGround = false;
}

Level& LevelManager::currentLevel() {
  return level;
}

bool LevelManager::isComplete() const {
  return complete;
}

int LevelManager::currentIndex() const {
  return index;
}