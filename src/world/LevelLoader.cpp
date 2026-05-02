#include "world/LevelLoader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Config.h"
#include "utils/PathUtils.h"

using namespace std;

bool LevelLoader::load(const string& levelFilePath, Level& level) const {
  string   fullPath = getAssetPath(levelFilePath);
  ifstream file(fullPath);

  if (!file.is_open()) {
    cerr << "[LevelLoader] couldn't open: " << levelFilePath << "\n";
    return false;
  }

  // Reset level to clean state before populating
  level.tiles.clear();
  level.keys.clear();
  level.bgLayers.clear();
  level.hasExit = false;

  string section = "none";
  string theme   = "ocean";
  string line;

  while (getline(file, line)) {
    if (line.empty() || line[0] == '#')
      continue;

    istringstream ss(line);
    string        token;
    ss >> token;

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
      getline(ss, level.name);
      if (!level.name.empty() && level.name[0] == ' ') {
        level.name = level.name.substr(1);
      }
      continue;
    }

    if (token == "width") {
      ss >> level.worldWidth;
      continue;
    }
    if (token == "theme") {
      ss >> theme;
      continue;
    }
    if (token == "start") {
      ss >> level.playerStartX >> level.playerStartY;
      continue;
    }

    if (section == "tiles") {
      Tile t;
      t.x = stof(token);
      ss >> t.y >> t.width >> t.height >> t.r >> t.g >> t.b;
      level.tiles.push_back(t);
      continue;
    }

    if (section == "exit") {
      level.exitDoor.x = stof(token);
      ss >> level.exitDoor.y >> level.exitDoor.width >> level.exitDoor.height;
      level.hasExit = true;
      section       = "none";
      continue;
    }

    if (section == "keys") {
      Key k;
      k.x         = stof(token);
      k.collected = false;
      ss >> k.y >> k.width >> k.height;
      level.keys.push_back(k);
      continue;
    }
  }

  buildBackground(theme, level);

  cout << "[LevelLoader] Loaded: " << level.name << " (" << level.tiles.size() << " tiles)\n";

  return true;
}

void LevelLoader::buildBackground(const string& theme, Level& level) const {
  struct Palette {
    float skyTopR, skyTopG, skyTopB;
    float skyBotR, skyBotG, skyBotB;
    float midR, midG, midB;
    float nearR, nearG, nearB;
  };

  Palette p = {};  // zero-initialised — fallback if theme not matched

  if (theme == "desert") {
    p = {0.85f, 0.60f, 0.30f, 0.95f, 0.80f, 0.50f, 0.70f, 0.50f, 0.25f, 0.55f, 0.38f, 0.18f};
  } else if (theme == "mountain") {
    p = {0.55f, 0.65f, 0.80f, 0.75f, 0.82f, 0.90f, 0.50f, 0.50f, 0.55f, 0.35f, 0.38f, 0.40f};
  }

  ParallaxLayer sky(BACKGROUND_LAYER_1_SPEED);
  sky.bands.push_back({HORIZON_Y, (float)WINDOW_HEIGHT, p.skyTopR, p.skyTopG, p.skyTopB});
  sky.bands.push_back({(float)GROUND_SURFACE_Y, HORIZON_Y, p.skyBotR, p.skyBotG, p.skyBotB});
  level.bgLayers.push_back(sky);
}