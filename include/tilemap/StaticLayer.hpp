#pragma once

#include "Layer.hpp"
#include "TileType.hpp"

namespace Tm
{
    class StaticLayer : public Layer
    {
    public:
        StaticLayer(const sf::Vector2i &size);
        ~StaticLayer() override = default;

        /// @remarks For the Ground Layer, that only means of the tile is walkable (and exists) or not.
        bool canMoveTo(const sf::Vector2i &tileCoords) const override;

        /// @brief getter and setter for tile position
        const TileType *operator[](const sf::Vector2i &tileCoords) const;
        const TileType *&operator[](const sf::Vector2i &tileCoords);

        /**
         * @param pos The position to check.
         * @return Whether there is a tile at the given position.
         */
        bool contains(const sf::Vector2i &pos) const;

    private:
        /// Region. If a tile is NULL, that's mean the position is outside the region.
        std::vector<std::vector<const TileType *>> m_tiles;
    };
}


