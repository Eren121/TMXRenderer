
#include "tilemap/TileType.hpp"

namespace Tm
{
    TileType::TileType(const tmx::Tileset::Tile &tmx_tile, const tmx::Tileset &parent)
        : m_tmx_tile(tmx_tile),
          m_gid(parent.getFirstGID() + tmx_tile.ID)
    {
        m_properties = Property::asMap(tmx_tile.properties);
        m_walkable = Property::getOrDefault(m_properties, "walkable", false);

        // walkable will have another strategy (layer to determine it?)
        m_walkable = true;
    }

    bool TileType::walkable() const
    {
        return m_walkable;
    }
}