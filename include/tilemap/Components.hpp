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
        /**
         * @brief How many tiles the player can see in each direction left, right for X, and up and down for Y.
         */
        sf::Vector2<int> sight;

        /**
         * @return The real viewport size in tile count,
         *         because @ref Player.sight gives size in one direction, minus the one
         *         the player is. The viewport is always a square.
         */
        sf::Vector2<int> viewportSize() const
        {
            return sight * 2 + 1;
        }
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

    /**
     * A character or an object that is moving between two tiles
     */
    struct Moving
    {
        explicit Moving(const vec2i &target, const vec2i &origin)
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