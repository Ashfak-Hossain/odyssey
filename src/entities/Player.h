#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "entities/Key.h"
#include "entities/Rect.h"
#include "systems/InputManager.h"

/**
 * @brief This is the character in the game.
 */
class Player {
 public:
  // Constructs a player at the origin with zero velocity and full health.
  Player();

  float x, y;            // bottom left corner of the player bounding box
  float vx, vy;          // velocity (pixels/sec)
  float height, width;   // size of the player bounding box
  bool  onGround;        // true when player is on the ground
  float startX, startY;  // spawn position for this level (Level manager sets this)
  bool  hasKey = false;  // true if al keys are collected

  static constexpr int MAX_HEALTH = 3;  // can be dead 3 times max
  int                  health     = MAX_HEALTH;

  /**
   * @brief player's axis-aligned bounding box.
   *
   * @return AABB with bottom-left at (x, y).
   */
  Rect getRect() const;

  /**
   * @brief Applies gravity to player.`vy`.
   * By `Physics::update()` will call this in every frame to apply gravity to the
   * player.
   *
   * @param deltaTime time elapsed since last frame(in seconds)
   */
  void applyGravity(float deltaTime);

  /**
   * @brief Gives the player an upward velocity.
   * Only works when `onGround` is true. can't double jump in mid-air
   */
  void jump();

  /**
   * @brief sets horizontal velocity to the left side (x -> negative)
   */
  void moveLeft();

  /**
   * @brief sets horizontal velocity to the right side (x -> positive)
   */
  void moveRight();

  /**
   * @brief sets horizontal movement 0.
   */
  void stopMoving();

  /**
   * @brief  Resets the player to their spawn position with 0 velocity.
   * Sets (x, y) to (startX, startY).
   */
  void respawn();

  /**
   * @brief
   * - lose 1 health and respawn;
   */
  void takeDamage();

  /**
   * @brief change input state into player movement calls.
   *
   * @param inputManager reference of which keys are held this frame.
   */
  void applyInput(const InputManager& inputManager);

  /**
   * @brief  Checks each key in `keys` for overlap with the player and collects it.
   *
   * @param keys Mutable list of keys of the current level
   */
  void collectKeys(std::vector<Key>& keys);

  /**
   * @brief check if a player is fallen out of the world
   */
  bool checkFall();
};

#endif  // PLAYER_H