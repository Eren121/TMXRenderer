#pragma once

#include "TileType.hpp"
#include "Property.hpp"
#include "Direction.hpp"
#include "common.hpp"
#include <tuple>
#include <tmxlite/Tileset.hpp>

namespace Tm
{
    /// Merge all tilesets files (.tsx files)
    /// one Tm::Tileset can represent multiple tmx:Tileset
    class Tileset
    {
    public:
        Tileset();
        ~Tileset() = default;

        /// Create a Tileset by merging multiple files
        /// tmx:: is really just a wrapper and parser around .tmx files
        void create(const std::vector<tmx::Tileset> &tmx_tilesets);

        const TileType &operator[](GID gid) const;

        bool contains(GID gid) const { return m_tiles.contains(gid); }

        /// Get the tile for a character from the character's type name. A character can be the player, PNG, mobs...
        /// Returns 0 if the tile is not found
        GID getCharacterTile(const string &objectType, Direction direction, bool isMoving) const;

    private:
        std::vector<tmx::Tileset> m_tmx_tilesets;

        /// Parsed tiles map
        std::map<GID, TileType> m_tiles;

        /// Key is a tuple of: type, direction, isMoving
        std::map<std::tuple<string, Direction, bool>, GID> m_charactersTile;
    };
}


