#ifndef LEVELMANAGER_H

#define LEVELMANAGER_H

#include <string>
#include <vector>

#include "entities/Player.h"
#include "world/Level.h"
#include "world/LevelLoader.h"

/**
 * @brief Controls level sequence and transition logic.
 *
 * - Maintains the ordered list of level file paths (@ref levelPaths).
 * - Holds the single active @ref Level, loaded from level files on demand.
 * - Shows all states so @ref Game can trigger fade transitions at right place.
 * - Resets the full sequence on game-over.
 */
class LevelManager {
 private:
  std::vector<std::string> levelPaths;  // path of the levels (declared in construction)
  Level                    level;       // hold all static data in a level.
  LevelLoader              loader;      // Loads a Level from a .txt file
  int                      index;       // 0-based index in levelPaths for the active level
  bool                     complete;    // true if all level ar passed

  /**
   * @brief Loads levelPaths[index] into @ref level and resets the player to the spawn point.
   *
   * Resets player position, velocity, onGround flag, and hasKey flag so state
   * from the previous level does not affect into the new level.
   *
   * @param player Player to reposition at the new level's start coordinates.
   */
  void loadCurrent(Player& player);

 public:
  /**
   * @brief defines the ordered level file paths
   */
  LevelManager();

  /**
   * @brief Resets progress to level 0 and loads it. called only once before the game loop
   *
   * @param player Player to spawn at the first level's start position.
   */
  void init(Player& player);

  /**
   * @brief Returns true when the player should move to the next level.
   *
   * Conditions: the level has an exit, the player carries the keys,
   * and the player's rect overlaps the exit door rect.
   * This function does not advance itselt — @ref Game calls this when starting to fade,
   * then calls @ref advance after the fade-out completes.
   *
   * @param player Player to test against the exit door.
   */
  bool shouldAdvance(const Player& player) const;

  /**
   * @brief Increments level index and loads the next level.Sets complete if there are no more.
   * If index exceeds the last path, sets @ref complete and prints a completion message.
   *
   * @note only be called after @ref shouldAdvance returns true.
   * @param player Player to spawn at the next level's start coordinates.
   */
  void advance(Player& player);

  /**
   * @brief Resets to level 0 and reloads it. Called on player death.
   *
   * @param player Player to repositoin at level 1 start coords.
   */
  void resetToFirst(Player& player);

  /**
   * @brief Returns a mutable reference to the currently loaded level.
   */
  Level& currentLevel();

  /**
   * @brief Returns a read-only reference to the currently loaded level.
   */
  const Level& currentLevel() const;

  /**
   * @brief Returns true if all levels have been completed
   */
  bool isComplete() const;

  /**
   * @brief Returns the 0-based index of the currently active level.
   */
  int currentIndex() const;
};

#endif  // LEVELMANAGER_H