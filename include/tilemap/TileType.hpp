#pragma once

#include "common.hpp"
#include <tmxlite/Tileset.hpp>
#include "Property.hpp"

namespace Tm
{
    using GID = int;

    /**
     * @brief A type of tile. Do not represent one specific tile position,
     *        but instead the type shared between all tiles of the same type.
     * @example If the region is 30x30 made of full water,
     *          there is only one TileType reference shared that represent a water tile.
     */
    class TileType final
    {
    public:
        /// For keyable
        TileType() = default;
        TileType(const tmx::Tileset::Tile &tile, const tmx::Tileset &parent);
        ~TileType() = default;

        /// @remarks Returns false means a character can't move to this tile
        bool walkable() const;

        /// Returns the underlying TMX tile
        const auto& tmx() const { return m_tmx_tile; }

        /// Global tile id (starts at 1)
        auto gid() const { return m_gid; }

        /// Local tile id (relative to the tileset, starts at 0)
        auto lid() const { return m_tmx_tile.ID; }

    private:
        tmx::Tileset::Tile m_tmx_tile;
        PropertiesMap m_properties;
        bool m_walkable{false};
        GID m_gid;
    };
}

