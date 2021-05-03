#include "tilemap/Layer.hpp"
#include "config/Math.hpp"

namespace Tm
{
    Layer::Layer(const sf::Vector2i &size)
        : AbstractLayer(size),
          m_tiles(create2DVector<const TileType *>(size))
    {

    }

    bool Layer::canMoveTo(const sf::Vector2i &pos) const
    {
        bool ret(false);

        if (pos.x >= 0 && pos.y >= 0 && pos.x < width() && pos.y < height())
        {
            auto tile = m_tiles[pos.x][pos.y];

            if (tile)
            {
                if (tile->walkable())
                {
                    ret = true;
                }
            }
        }

        return ret;
    }

    const TileType *Layer::operator[](const sf::Vector2i &tileCoords) const
    {
        return m_tiles[tileCoords.x][tileCoords.y];
    }

    const TileType *&Layer::operator[](const sf::Vector2i &tileCoords)
    {
        return m_tiles[tileCoords.x][tileCoords.y];
    }

    bool Layer::isTileEmpty(const sf::Vector2i &pos) const
    {
        bool ret(true);

        if (pos.x >= 0 && pos.y >= 0 && pos.x < width() && pos.y < height())
        {
            if (m_tiles[pos.x][pos.y] != nullptr)
            {
                ret = false;
            }
        }

        return ret;
    }

    int Layer::getGID(vec2i pos) const
    {
        if(isTileEmpty(pos))
        {
            return 0;
        }
        else
        {
            return (*this)[pos]->tmx().ID;
        }
    }
}