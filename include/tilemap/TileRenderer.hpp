#pragma once

#include "TileType.hpp"
#include "common.hpp"
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace Tm
{
    class TilemapRenderer
    {
    public:
        TilemapRenderer() = default;

        /// @brief Draw a tile as a rect of size 1 at origin.
        /// @remarks Centralize the rendering of one tile, avoid code duplication because
        ///          how the layers are rendered is different between objects (iterate entities) and tile layers (iterate coords)
        /// @remarks Ignore animations (object animation is from a local clock, and tile is from a global one)
        void drawTile(sf::RenderTarget& target, const TileType &tile, const sf::Transform &parentTransform);

    private:

        /// Get the texture from an ID (texture's path)
        /// Load it if not already loaded
        const sf::Texture& cacheTexture(const std::string& id);

        /// "Pool" of textures
        /// Contains all the textures
        /// Load on the fly the needed textures from sprites
        /// key: the name of the file of the texture (relative path from the map file's directory)
        std::map<std::string, sf::Texture> m_texturesResource;
    };
}