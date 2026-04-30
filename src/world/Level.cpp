#include "Level.h"

#include <string.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "Config.h"
#include "entities/Key.h"
#include "utils/PathUtils.h"
#include "utils/Platform.h"
#include "world/Level.h"

using namespace std;

Level::Level()
    : worldWidth(WORLD_WIDTH),
      playerStartX(100),
      playerStartY(GROUND_SURFACE_Y),
      exitDoor{0, 0, 0, 0},
      hasExit(false) {
}

bool Level::load(const string& levelFilePath) {
  string   fullPath = getAssetPath(levelFilePath);
  ifstream file(fullPath);
  // if can't open file or read file, return false and print error message
  if (!file.is_open()) {
    cerr << "[Level] couldn't open : " << levelFilePath << "\n";
    return false;
  }

  tiles.clear();
  keys.clear();
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

    if (token == "keys") {
      section = "keys";
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

    if (section == "keys") {
      Key k;
      k.x = stof(token);
      ss >> k.y >> k.width >> k.height;
      k.collected = false;
      keys.push_back(k);
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
  // Color palettes per theme
  struct Palette {
    float skyTopR, skyTopG, skyTopB;
    float skyBotR, skyBotG, skyBotB;
    float midR, midG, midB;
    float nearR, nearG, nearB;
  };

  Palette p;

  if (theme == "desert") {
    p = {0.85f, 0.60f, 0.30f, 0.95f, 0.80f, 0.50f, 0.70f, 0.50f, 0.25f, 0.55f, 0.38f, 0.18f};
  } else if (theme == "mountain") {
    p = {0.55f, 0.65f, 0.80f, 0.75f, 0.82f, 0.90f, 0.50f, 0.50f, 0.55f, 0.35f, 0.38f, 0.40f};
  }

  {
    ParallaxLayer sky(BACKGROUND_LAYER_1_SPEED);
    sky.bands.push_back({HORIZON_Y, (float)WINDOW_HEIGHT, p.skyTopR, p.skyTopG, p.skyTopB});
    sky.bands.push_back({(float)GROUND_SURFACE_Y, HORIZON_Y, p.skyBotR, p.skyBotG, p.skyBotB});
    bgLayers.push_back(sky);
  }
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

void Level::renderKeys() const {
  for (const auto& key : keys) {
    key.render();
  }
}

void Level::renderExit(bool locked) const {
  if (!hasExit)
    return;

  if (locked) {
    glColor3f(EXIT_LOCKED_FILL_R, EXIT_LOCKED_FILL_G, EXIT_LOCKED_FILL_B);
  } else {
    glColor3f(EXIT_UNLOCKED_FILL_R, EXIT_UNLOCKED_FILL_G, EXIT_UNLOCKED_FILL_B);
  }
  glBegin(GL_QUADS);
  glVertex2f(exitDoor.x, exitDoor.y);
  glVertex2f(exitDoor.x + exitDoor.width, exitDoor.y);
  glVertex2f(exitDoor.x + exitDoor.width, exitDoor.y + exitDoor.height);
  glVertex2f(exitDoor.x, exitDoor.y + exitDoor.height);
  glEnd();

  if (locked) {
    glColor3f(EXIT_LOCKED_BORDER_R, EXIT_LOCKED_BORDER_G, EXIT_LOCKED_BORDER_B);
  } else {
    glColor3f(EXIT_UNLOCKED_BORDER_R, EXIT_UNLOCKED_BORDER_G, EXIT_UNLOCKED_BORDER_B);
  }
  glLineWidth(EXIT_BORDER_LINE_WIDTH);
  glBegin(GL_LINE_LOOP);
  glVertex2f(exitDoor.x, exitDoor.y);
  glVertex2f(exitDoor.x + exitDoor.width, exitDoor.y);
  glVertex2f(exitDoor.x + exitDoor.width, exitDoor.y + exitDoor.height);
  glVertex2f(exitDoor.x, exitDoor.y + exitDoor.height);
  glEnd();
}