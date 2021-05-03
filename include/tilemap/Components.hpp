#pragma once

#include "common.hpp"
#include "Direction.hpp"

namespace Tm
{

    /**
     * @brief Each object of the tilemap must have a position.
     * @remark Component
     */
    using Position = sf::Vector2<int>;

    /**
     * @brief Represent the player.
     * @remark Component
     */
    struct Player
    {
    };

    /**
     * Living object, like a trainer, or the player itself.
     */
    struct Character
    {
        explicit Character(const std::string &name, sf::Time speed = sf::milliseconds(200))
            : name(name), speed(speed), facingDirection(Direction::DOWN) {}


        std::string name;

        /**
         * @brief The duration to move from one tile to another for a character.
         * @remark Define the speed of the player.
         */
        sf::Time speed;

        Direction facingDirection;
    };

    /// Entity that has a tile associated
    struct Sprite
    {
        explicit Sprite(int gidForAll = 0)
        {
            for(auto dir : magic_enum::enum_values<Direction>())
            {
                gids[dir] = gidForAll;
                gidsMoving[dir] = gidForAll;
            }
        }

        /// Tile ID for each facing direction.
        /// If the Sprite is not orientable, the values are all the same.
        /// Each sprite has also a tileID when moving

        int gid(Direction dir, bool moving = false) const
        {
            const auto &map = (moving ? gidsMoving : gids);
            return map.at(dir);
        }

        /// Contains always for each direction (0 by default)
        std::map<Direction, int> gids;
        std::map<Direction, int> gidsMoving;
    };

    /// Dynamic component used for animation (not used if no animation)
    struct SpriteIsAnimating
    {
        /// GID of the animated tile
        int gid{0};

        /// Index of the frame
        int frame{0};

        /// Time when the current frame started (and not the first overall frame)
        sf::Time start{sf::Time::Zero};
    };

    /**
     * A character or an object that is moving between two tiles
     */
    struct IsMoving
    {
        explicit IsMoving(const vec2i &target, const vec2i &origin)
            : startingTime(sf::getCurrentTime()), destination(target), interpolatedPos(origin) {}

        /// The time the character has started moving
        sf::Time startingTime;
        vec2i destination;

        /// The position interpolated each frame between origin and destination
        vec2f interpolatedPos;
    };

    /**
     * Talkable object, that should open a GUI to display the text.
     * Like a interactive character.
     */
    struct Dialog
    {
        std::string text;
    };
}