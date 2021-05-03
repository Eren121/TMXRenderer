#include "controller/Command.hpp"

bool getInputDirection(Command cmd, vec2i &out)
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
