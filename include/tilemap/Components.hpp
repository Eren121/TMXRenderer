#pragma once

#include <SFML/System/Vector2.hpp>
#include "config/Math.hpp"

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
     *
     */
    struct Object
    {

    };

}