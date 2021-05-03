#pragma once

#include "Layer.hpp"
#include "TileType.hpp"

namespace Tm
{
    class LayerOfTiles : public Layer
    {
    public:
        explicit LayerOfTiles(const sf::Vector2i &size);
        ~LayerOfTiles() override = default;

        /// @remarks For the Ground Layer, that only means of the tile is walkable (and exists) or not.
        bool canMoveTo(const sf::Vector2i &pos) const override;

        /// @brief getter and setter for tile position
        const TileType *operator[](const sf::Vector2i &tileCoords) const;
        const TileType *&operator[](const sf::Vector2i &tileCoords);

        bool isTileEmpty(const sf::Vector2i &pos) const override;

        /// @remarks returns 0 if there is no tile at this position
        GID getGID(vec2i pos) const;

        void render(sf::RenderTarget &target, TileRenderer &renderer, const sf::IntRect &bounds,
                    const sf::Transform &parentTransform) const override;

    private:
        /// Region. If a tile is NULL, that's mean the position is outside the region.
        std::vector<std::vector<const TileType *>> m_tiles;
    };
}


