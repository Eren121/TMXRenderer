#pragma once

#include <entt/entt.hpp>
#include <SFML/System.hpp>

namespace Tm
{
    /**
     * @brief One layer of the region.
     * A region is composed of multiple layers:
     *  - One layer of ground (static)
     *  - One layer of decoration object (static)
     *  - One layer of characters, moveable objects (dynamic)
     */
    class Layer
    {
    public:
        Layer(const sf::Vector2i &size);
        virtual ~Layer() = default;

        int width() const;
        int height() const;

        /**
         * @return Wether a character can be placed at this position:
         *         the tile exists, is non-walkable, and no other character is already at this position.
         */
        virtual bool canMoveTo(const sf::Vector2i &tileCoords) const = 0;

    protected:
        sf::Vector2i m_size;
    };
}