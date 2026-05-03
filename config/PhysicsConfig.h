#ifndef PHYSICS_CONFIG_H
#define PHYSICS_CONFIG_H

constexpr float GRAVITY        = -600.0f;  // gravity acceleration (pixels/s^2)
constexpr float JUMP_FORCE     = 320.0f;   // initial jump velocity (pixels/s)
constexpr float MOVE_SPEED     = 200.0f;   // horizontal movement speed (pixels/s)
constexpr float FALL_THRESHOLD = -100.0f;  // y position, below this payer will take full damage

#endif  // PHYSICS_CONFIG_H