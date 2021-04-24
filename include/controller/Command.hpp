#pragma once

#include "common.hpp"

/**
 * @brief All commands. As the game can be played on a console, there is few commands.
 *        On keyboard, each one could be just a key.
 */
enum class Command {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    A,
    B,
    X,
    Y
};

/// If the command is a directional arrow, store the orientation in out
/// Returns true if the command is a directional arrow
/// Else return false. If false is returned, out is not changed
/// origin is top-left
static bool getInputDirection(Command cmd, vec2i &out)
{
    bool ret(true);
    vec2i dir{0, 0};

    switch (cmd)
    {
        case Command::LEFT:
            dir.x--;
            break;

        case Command::RIGHT:
            dir.x++;
            break;

        case Command::UP:
            dir.y--;
            break;

        case Command::DOWN:
            dir.y++;
            break;

        default:
            ret = false;
            break;
    }

    if (ret)
    {
        out = dir;
    }

    return ret;
}