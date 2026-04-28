#ifndef LEVELMANAGER_H

#define LEVELMANAGER_H

#include <string>
#include <vector>

#include "Level.h"
#include "Player.h"

/**
 * @brief LevelManager controls level sequences and transition logics between levels
 * - handles ordered list of level file paths @ref levelPaths
 * - current loaded level data @ref level
 * - load the next level
 * - update game when all levels are complete
 */
class LevelManager {
 private:
  std::vector<std::string> levelPaths;
  Level                    level;
  int                      index;     // index of current
  bool                     complete;  // track all levels are complete or not

  /**
   * @brief
   *
   * @param player
   */
  void loadCurrent(Player& player);

 public:
  LevelManager();

  /**
   * @brief
   *
   * @param player
   */
  void init(Player& player);

  /**
   * @brief
   *
   * @param player
   */
  void update(Player& player);

  /**
   * @brief
   *
   * @return Level&
   */
  Level& currentLevel();

  /**
   * @brief
   *
   * @return true
   * @return false
   */
  bool isComplete() const;

  /**
   * @brief
   *
   * @return int
   */
  int currentIndex() const;
};

#endif