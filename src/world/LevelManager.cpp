#include "world/LevelManager.h"

#include <iostream>

#include "world/BackgroundThemes.h"

LevelManager::LevelManager() : index(0), complete(false) {
  levelPaths = {
      "levels/level1.txt",
      "levels/level2.txt",
  };
}

// --------------- init ---------------
void LevelManager::init(Player& player) {
  index    = 0;
  complete = false;
  loadCurrent(player);
}

// --------------- should advance ---------------
bool LevelManager::shouldAdvance(const Player& player) const {
  if (complete || !level.hasExit) {
    return false;
  }
  bool go = player.hasKey && player.getRect().overlaps(level.exitDoor);
  return go;
}

// --------------- advance ---------------
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

// --------------- resetToFirst ---------------
void LevelManager::resetToFirst(Player& player) {
  index    = 0;
  complete = false;
  loadCurrent(player);
}

// --------------- loadCurrent ---------------
void LevelManager::loadCurrent(Player& player) {
  bool loaded = loader.load(levelPaths[index], level);

  if (!loaded) {
    std::cerr << "[LevelManager] failed to load: " << levelPaths[index] << "\n";
  }

  BackgroundThemes::build(index, level.bgLayers);

  player.startX   = level.playerStartX;
  player.startY   = level.playerStartY;
  player.x        = level.playerStartX;
  player.y        = level.playerStartY;
  player.vx       = 0;
  player.vy       = 0;
  player.onGround = false;
  player.hasKey   = false;
}

// --------------- currentLevel ---------------
Level& LevelManager::currentLevel() {
  return level;
}

// --------------- currentLevel static ---------------
const Level& LevelManager::currentLevel() const {
  return level;
}

// --------------- isComplete ---------------
bool LevelManager::isComplete() const {
  return complete;
}

// --------------- current ---------------
int LevelManager::currentIndex() const {
  return index;
}