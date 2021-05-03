#pragma once

#include "AbstractLayer.hpp"
#include "TileType.hpp"

namespace Tm
{
    class Layer : public AbstractLayer
    {
    public:
        Layer(const sf::Vector2i &size);
        ~Layer() override = default;

        /// @remarks For the Ground AbstractLayer, that only means of the tile is walkable (and exists) or not.
        bool canMoveTo(const sf::Vector2i &pos) const override;

        /// @brief getter and setter for tile position
        const TileType *operator[](const sf::Vector2i &tileCoords) const;
        const TileType *&operator[](const sf::Vector2i &tileCoords);

        /**
         * @param pos The position to check.
         * @return Whether there is a tile at the given position.
         */
        bool isTileEmpty(const sf::Vector2i &pos) const;

        /// returns 0 is there is no tile at this position
        GID getGID(vec2i pos) const;

        /// Name of the layer
        auto &name() const { return m_name; }
        void setName(const string &name) { m_name = name; }

    private:
        /// Region. If a tile is NULL, that's mean the position is outside the region.
        std::vector<std::vector<const TileType *>> m_tiles;
        string m_name;
    };
}


