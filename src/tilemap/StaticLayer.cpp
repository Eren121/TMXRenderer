#include "tilemap/StaticLayer.hpp"
#include "config/Math.hpp"

namespace Tm
{
    StaticLayer::StaticLayer(const sf::Vector2i &size)
        : Layer(size),
          m_tiles(create2DVector<const TileType *>(size))
    {

    }

    bool StaticLayer::canMoveTo(const sf::Vector2i &tileCoords) const
    {
        bool ret(false);
        auto tile = m_tiles[tileCoords.x][tileCoords.y];

        if (tile)
        {
            if (tile->walkable())
            {
                ret = true;
            }
        }

        return ret;
    }

    const TileType *StaticLayer::operator[](const sf::Vector2i &tileCoords) const
    {
        return m_tiles[tileCoords.x][tileCoords.y];
    }

    const TileType *&StaticLayer::operator[](const sf::Vector2i &tileCoords)
    {
        return m_tiles[tileCoords.x][tileCoords.y];
    }

    bool StaticLayer::contains(const sf::Vector2i &pos) const
    {
        bool ret(false);

        if (pos.x >= 0 && pos.y >= 0 && pos.x < width() && pos.y < height())
        {
            if (m_tiles[pos.x][pos.y] != nullptr)
            {
                ret = true;
            }
        }

        return ret;
    }
}