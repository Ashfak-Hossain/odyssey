#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include <string>

#include "world/Level.h"

/**
 * @brief Loads a Level from a .txt file and builds its background layers.
 *
 * manage all file I/O and parallax construction logic.
 *
 * Text file format:
 *   name    <string>
 *   width   <float>
 *   start   <x> <y>
 *   tiles   (section header, followed by rows: x y w h r g b)
 *   exit    x y w h
 *   keys    (section header, followed by rows: x y w h)
 */
class LevelLoader {
 public:
  /**
   * @brief Parse levelFilePath (relative to assets/) and populate level.
   * Clears all existing level data before loading.
   *
   * @param levelFilePath path relative to assets/ dir ("levels/level1.txt")
   * @param level         Level object to populate
   * @return true  on success, false if file cannot be opened
   */
  bool load(const std::string& levelFilePath, Level& level) const;
};

#endif  // LEVEL_LOADER_H