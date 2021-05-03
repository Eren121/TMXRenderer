#pragma once
#include "common.hpp"

/**
 * @brief Direction is facing a character in the world.
 */
enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

/**
 * @return The unit vector corresponding to the direction, centered in (0, 0).
 */
vec2i facingVector(Direction dir);

Direction facingDirection(vec2i vec);

/// Rotations are counterclockwise, DOWN is default orientation.
/// Returns in degrees.
/// DOWN is 0°
/// LEFT is 90°
/// RIGHT is -90°
/// UP is 180°.
float getAngle(Direction dir);