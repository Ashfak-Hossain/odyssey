#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "entities/Key.h"
#include "entities/Rect.h"
#include "systems/InputManager.h"

class LevelManager;

class Player {
 public:
  Player();

  float x, y;           // bottom left corner of the player bounding box
  float vx, vy;         // velocity in pixel/sec
  float height, width;  // size of the player bounding box
  bool  onGround;

  float startX, startY;  // spawn position for this level (Level manager sets this)
  bool  hasKey = false;

  static constexpr int MAX_HEALTH = 3;
  int                  health     = MAX_HEALTH;

  // returns the bounding box of the player
  Rect getRect() const;

  /**
   * @brief handle gravity of the player.
   * Game::update() will call this in every frame to apply gravity to the player.
   * @param deltaTime time elapsed since last frame(in seconds)
   */
  void applyGravity(float deltaTime);
  void jump();
  void moveLeft();
  void moveRight();
  void stopMoving();

  /**
   * @brief
   * - reset to startX/Y, velocity = 0
   */
  void respawn();

  /**
   * @brief
   * - lose 1 health and respawn;
   */
  void takeDamage();

  void applyInput(const InputManager& inputManager);
  void collectKeys(std::vector<Key>& keys);
  void checkFall(LevelManager& levelManager);
};

#endif  // PLAYER_H