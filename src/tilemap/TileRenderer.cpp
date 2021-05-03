#include "TileRenderer.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

namespace Tm
{
    void TileRenderer::drawTile(sf::RenderTarget &target, const Tm::TileType &tile, const sf::Transform &parentTransform)
    {
        const auto &info = tile.tmx();
        const auto &textureFile = info.imagePath;
        const auto &imagePosition(info.imagePosition);
        const auto &imageSize(info.imageSize);
        const auto &texture = cacheTexture(textureFile);
        const IntRect textureRect(imagePosition.x, imagePosition.y,
                                  imageSize.x, imageSize.y);

        // Sprite sub-rect in pixel in local texture file
        sf::Sprite sprite(texture, textureRect);

        sf::Transform model;

        // Make the tile size (1, 1)
        model.scale(1.0f / sf::size(sprite.getTextureRect()));

        const sf::Transform mvp = parentTransform * model;
        target.draw(sprite, mvp);
    }

    const sf::Texture &TileRenderer::cacheTexture(const string &id)
    {
        if (!m_texturesResource.contains(id))
        {
            /// Texture not already loaded, load it
            auto &texture = m_texturesResource[id];

            /// Assert the texture is found
            /// If the texture is not found, exit with error
            assert(texture.loadFromFile(assets::getFilePath(id)));
        }

        /// Now texture should always been already/just preloaded, just get a pointer to it
        const auto &texture = m_texturesResource.at(id);

        return texture;
    }
}
