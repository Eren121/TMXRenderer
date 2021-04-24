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