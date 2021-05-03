#include "tilemap/TileRenderer.hpp"
#include "tilemap/Tileset.hpp"
#include "tilemap/Components.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

namespace Tm
{
    TileRenderer::TileRenderer(const Tileset &tileset)
        : m_tileset(tileset)
    {
    }

    void
    TileRenderer::drawTile(sf::RenderTarget &target, const Tm::TileType &tile, const sf::Transform &parentTransform)
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

            cout << "loading texture " << id << endl;
        }

        /// Now texture should always been already/just preloaded, just get a pointer to it
        const auto &texture = m_texturesResource.at(id);

        return texture;
    }

    const TileType *TileRenderer::updateAnimation(int &gid, entt::registry &registry, entt::entity entity)
    {
        const TileType *ret(nullptr);

        // If gid is not known, do not change it
        if (m_tileset.contains(gid))
        {
            const auto &frames = m_tileset[gid].tmx().animation.frames;

            // Animate the sprite if this tile is animated by Tiled Animator Editor
            if (!frames.empty())
            {
                auto &anim = registry.get_or_emplace<Tm::SpriteIsAnimating>(entity, Tm::SpriteIsAnimating{
                    .gid = gid,
                    .frame = 0,
                    .start = sf::getCurrentTime(),
                });

                if(gid != anim.gid)
                {
                    // The sprite has changed, reset the animation
                    anim.gid = gid;
                    anim.frame = 0;
                    anim.start = sf::getCurrentTime();
                }

                // Take pointer to allow iteration (incrementation to take next frame)
                // Reference can't be rebounds
                const auto *frame = &frames.at(anim.frame);

                // Convert to sf::Time
                Time frameDuration = milliseconds(frame->duration);
                const Time currentTime = getCurrentTime();


                // Search next frame if needed
                // Unlikely, under some circonstances (like lag, high rate animation), skip multiples frames
                // But likely +1 frame or +0 (same frame)
                while (currentTime > anim.start + frameDuration)
                {
                    // Add time (step by step)
                    anim.start += frameDuration;

                    // Increment frame
                    anim.frame++;
                    if (anim.frame >= int(frames.size()))
                    {
                        anim.frame = 0;
                    }

                    // Get updated frameDuration
                    frame = &frames.at(anim.frame);
                    frameDuration = milliseconds(frame->duration);
                }

                // Tiled save tile ID of animations relative to the tileset (LID)
                // But tmx convert it to GID, so we already have it.
                // This does not means we can use tiles from different tilesets for one animation;
                // it's actually not possible inside Tiled Editor (but may be possible in the engine)
                gid = frames.at(int(anim.frame)).tileID;

                if (gid == 0)
                {
                    // Zero is null tile
                    cerr << "warning: null tile in animation" << endl;
                }
            }
        }

        if(m_tileset.contains(gid))
        {
            ret = &m_tileset[gid];
        }

        return ret;
    }
}
