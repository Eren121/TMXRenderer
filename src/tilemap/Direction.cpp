#include "tilemap/Direction.hpp"

vec2i facingVector(Direction dir)
{
    vec2i ret;

    switch (dir)
    {
        case Direction::UP:
            ret.y--;
            break;

        case Direction::DOWN:
            ret.y++;
            break;

        case Direction::LEFT:
            ret.x--;
            break;

        case Direction::RIGHT:
            ret.x++;
            break;

        default:
            cerr << "warning: unkown direction: " << static_cast<int>(dir) << endl;
            // Returns (1, 0) by default (should never happend)
            ret.x++;
            break;
    }

    return ret;
}

Direction facingDirection(vec2i vec)
{
    Direction ret;
    const double angle = std::atan2(vec.y, vec.x);
    // atan2 returns in interval [-pi;+pi]

    // remember y is to down
    if (angle >= -3.0 * M_PI_4 && angle < -M_PI_4)
    {
        ret = Direction::UP;
    }
    else if (angle >= -M_PI_4 && angle < M_PI_4)
    {
        ret = Direction::RIGHT;
    }
    else if (angle >= M_PI_4 && angle < 3.0 * M_PI_4)
    {
        ret = Direction::DOWN;
    }
    else
    {
        ret = Direction::LEFT;
    }

    return ret;
}

float getAngle(Direction dir)
{
    switch (dir)
    {
        case Direction::UP:
            return 180.0f;
        case Direction::DOWN:
            return 0.0f;
        case Direction::LEFT:
            return 90.0f;
        case Direction::RIGHT:
            return -90.0f;
        default:
            cerr << "warning: unkown angle " << dir << endl;
            return 0.0f;
    }
}
