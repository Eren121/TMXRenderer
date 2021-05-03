#include "tilemap/LayerOfTiles.hpp"
#include "config/Math.hpp"
#include "config/Iterator2D.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

namespace Tm
{
    LayerOfTiles::LayerOfTiles(const Vector2i &size)
        : Layer(size),
          m_tiles(create2DVector<const TileType *>(size))
    {
        m_type = tmx::Layer::Type::Tile;
    }

    bool LayerOfTiles::canMoveTo(const Vector2i &pos) const
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
            else
            {
                // No tile, we can move on it
                ret = true;
            }
        }

        return ret;
    }

    const TileType *LayerOfTiles::operator[](const Vector2i &tileCoords) const
    {
        return m_tiles[tileCoords.x][tileCoords.y];
    }

    const TileType *&LayerOfTiles::operator[](const Vector2i &tileCoords)
    {
        return m_tiles[tileCoords.x][tileCoords.y];
    }

    bool LayerOfTiles::isTileEmpty(const Vector2i &pos) const
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

    int LayerOfTiles::getGID(vec2i pos) const
    {
        if (isTileEmpty(pos))
        {
            return 0;
        }
        else
        {
            return (*this)[pos]->gid();
        }
    }

    void LayerOfTiles::render(RenderTarget &target, TileRenderer &renderer, const IntRect &requestedBounds,
                              const Transform &parentTransform) const
    {
        /// If it is outside layer, don't render it
        IntRect bounds;
        bounds.left = clamp(requestedBounds.left, 0, width());
        bounds.top = clamp(requestedBounds.top, 0, height());
        bounds.width = clamp(requestedBounds.width, 0, width() - bounds.left);
        bounds.height = clamp(requestedBounds.height, 0, height() - bounds.top);

        for (const auto &pos : bounds)
        {
            /// Position as float (same values, just some function allows only vec2f and not vec2i)
            const vec2f fpos(pos);
            const auto type = m_tiles[pos.x][pos.y];

            // Check if there is a tile at this position
            if (type)
            {
                // Move into the tile coordinates
                Transform model;
                model = Transform().translate(fpos) * model;

                Transform combinedTransform = parentTransform * model;
                renderer.drawTile(target, *type, combinedTransform);
            }
        }
    }
}