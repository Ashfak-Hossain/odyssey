#include "world/Level.h"

#include "Config.h"

Level::Level()
    : worldWidth(WORLD_WIDTH),
      playerStartX(100),
      playerStartY(GROUND_SURFACE_Y),
      exitDoor{0, 0, 0, 0},
      hasExit(false) {
}
