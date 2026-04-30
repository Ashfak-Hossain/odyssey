
#include "world/LevelManager.h"

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

bool LevelManager::shouldAdvance(const Player& player) const {
  if (complete || !level.hasExit) {
    return false;
  }
  bool go = player.hasKey && player.getRect().overlaps(level.exitDoor);
  return go;
}

void LevelManager::advance(Player& player) {
  if (complete) {
    return;
  }

  index++;

  if (index >= (int)levelPaths.size()) {
    complete = true;
    std::cout << "[LevelManager] Game Complete!\n";
  } else {
    loadCurrent(player);
  }
}

void LevelManager::resetToFirst(Player& player) {
  index    = 0;
  complete = false;
  loadCurrent(player);
}

void LevelManager::loadCurrent(Player& player) {
  bool canLoad = level.load(levelPaths[index]);

  if (!canLoad) {
    std::cerr << "[LevelManager] failed to load levels\n";
  }

  player.startX   = level.playerStartX;
  player.startY   = level.playerStartY;
  player.x        = level.playerStartX;
  player.y        = level.playerStartY;
  player.vx       = 0;
  player.vy       = 0;
  player.onGround = false;
  player.hasKey   = false;
}

Level& LevelManager::currentLevel() {
  return level;
}

const Level& LevelManager::currentLevel() const {
  return level;
}

bool LevelManager::isComplete() const {
  return complete;
}

int LevelManager::currentIndex() const {
  return index;
}