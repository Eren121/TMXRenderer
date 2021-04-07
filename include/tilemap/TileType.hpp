#pragma once

#include "common.hpp"

namespace Tm
{
    /**
     * @brief A type of tile. Do not represent one specific tile position,
     *        but instead the type shared between all tiles of the same type.
     * @example If the region is 30x30 made of full water,
     *          there is only one TileType reference shared that represent a water tile.
     */
    class TileType final
    {
    public:
        TileType(const std::string &name, bool walkable, const sf::Vector2i &atlasPos);
        ~TileType() = default;

        /// @remarks Returns false means a character can't move to this tile
        bool walkable() const;

        const std::string &name() const;

        const sf::Vector2i &atlasPos() const;

    private:
        sf::Vector2i m_atlasPos;
        std::string m_name;
        bool m_walkable;
    };
}

