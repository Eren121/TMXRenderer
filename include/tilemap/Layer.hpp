#pragma once

#include <entt/entt.hpp>
#include <SFML/System.hpp>
#include "Loader.hpp"

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

        const vec2i& size() const { return m_size; }
        int width() const;
        int height() const;

        /**
         * @return Wether a character can be placed at this position:
         *         the tile exists, is non-walkable, and no other character is already at this position.
         */
        virtual bool canMoveTo(const sf::Vector2i &tileCoords) const = 0;

        PropertyMap &properties() { return m_properties; }

        const PropertyMap &properties() const { return m_properties; }

        const vec2f& scroll() const { return m_scroll; }
        vec2f& scroll() { return m_scroll; }

    protected:
        sf::Vector2i m_size;
        PropertyMap m_properties;
        vec2f m_scroll;
    };
}