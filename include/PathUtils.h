#ifndef PATHUTILS_H

#define PATHUTILS_H

#include <filesystem>
#include <string>

using std::string;

namespace fs = std::filesystem;

/**
 * @brief Get the full path of any file in assets dir
 *
 * relative = levels/level1.txt
 * Project root == "/Users/ashfakhossainevan/Development/odyssey"
 * fullPath == /Users/ashfakhossainevan/Development/odyssey/assets/levels/level1.txt
 *
 * @param relative file location in assets folder
 * @return string fullPath of the level file
 */
inline string getAssetPath(const string& relative) {
  fs::path projectRoot = fs::path(__FILE__).parent_path().parent_path();
  string   fullPath    = (projectRoot / "assets" / relative).string();
  return fullPath;
}

#endif