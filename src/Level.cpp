#include "Level.h"

#include <string.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "Config.h"

using namespace std;

Level::Level()
    : worldWidth(WORLD_WIDTH),
      playerStartX(100),
      playerStartY(GROUND_SURFACE_Y),
      exitDoor{0, 0, 0, 0},
      hasExit(false) {
}

bool Level::load(const string& levelFilePath) {
  ifstream file(levelFilePath);

  // if can't open file or read file, return false and print error message
  if (!file.is_open()) {
    cerr << "[Level] couldn't open : " << levelFilePath << "\n";
    return false;
  }

  tiles.clear();
  bgLayers.clear();
  hasExit = false;

  string section = "none";
  string theme   = "ocean";

  string line;

  while (getline(file, line)) {
    if (line.empty() || line[0] == '#') {
      continue;
    }

    istringstream ss(line);
    string        token;
    ss >> token;

    // Extracts section from token
    if (token == "tiles") {
      section = "tiles";
      continue;
    }
    if (token == "exit") {
      section = "exit";
      continue;
    }

    if (token == "name") {
      getline(ss, name);
      if (!name.empty() && name[0] == ' ') {
        name = name.substr(1);
      }
      continue;
    }

    if (token == "width") {
      ss >> worldWidth;
      continue;
    }

    if (token == "theme") {
      ss >> theme;
      continue;
    }

    if (token == "start") {
      ss >> playerStartX >> playerStartY;
      continue;
    }

    if (section == "tiles") {
      Tile t;
      t.x = stof(token);  // already read first token as value of x
      ss >> t.y >> t.width >> t.height >> t.r >> t.g >> t.b;
      tiles.push_back(t);
      continue;
    }

    if (section == "exit") {
      exitDoor.x = stof(token);
      ss >> exitDoor.y >> exitDoor.width >> exitDoor.height;
      hasExit = true;
      section = "none";
      continue;
    }
  }

  // build the background based on the theme
  buildBackground(theme);

  // Log the Level load result
  cout << "[Level] Loaded: " << name << " (" << tiles.size() << " tiles)\n";

  return true;
}

void Level::buildBackground(const string& theme) {
  bgLayers.clear();
}

/**
 * @brief render the tiles and objects in world space.
 */
void Level::renderForeground() const {
  for (const auto& tile : tiles) {
    tile.render();
  }
}

/**
 * @brief Each layer render with its own glLoadIdentity, glTranslatef separately.
 *
 * @param cameraX The horizontal position of the camera.
 *
 * @note Must be called before full camera transform
 */
void Level::renderBackground(float cameraX) const {
  for (const auto& layer : bgLayers) {
    layer.render(cameraX);
  }
}