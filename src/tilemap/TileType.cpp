
#include "tilemap/TileType.hpp"

namespace Tm
{
    TileType::TileType(const std::string &name, bool walkable, const sf::Vector2i &atlasPos)
        : m_name(name),
          m_walkable(walkable),
          m_atlasPos(atlasPos)
    {
    }

    bool TileType::walkable() const
    {
        return m_walkable;
    }

    const std::string &TileType::name() const
    {
        return m_name;
    }

    const sf::Vector2i &TileType::atlasPos() const
    {
        return m_atlasPos;
    }
}