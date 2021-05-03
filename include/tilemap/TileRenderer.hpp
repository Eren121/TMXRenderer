#pragma once

#include "common.hpp"
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace Tm
{
    class TileType;
    class Tileset;

    /// Pool of texture and individual tile renderer
    class TileRenderer
    {
    public:
        TileRenderer(const Tileset& tileset);

        /// @brief Draw a tile as a rect of size 1 at origin.
        /// @remarks Centralize the rendering of one tile, avoid code duplication because
        ///          how the layers are rendered is different between objects (iterate entities) and tile layers (iterate coords)
        /// @remarks Ignore animations (object animation is from a local clock, and tile is from a global one)
        void drawTile(sf::RenderTarget &target, const TileType &tile, const sf::Transform &parentTransform);

        /// For tiles that has animation (dynamic tiles)
        ///
        /// @remarks If the animation reached a new step, @p gid is updated and also the entity state.
        /// @remarks If there is no animation or it's the same frame, the gid is not changed.
        /// @remarks If the entity is currently animated but by an animation different from @p gid,
        ///          (may happens if the sprite is changed but the animation has not finished yet)
        ///          it reset the animation as the first frame with @p gid as the new animation.
        /// @remarks The animation state is stored inside a component of the entity
        /// @param gid The GID of the animated Tile.
        /// @returns A pointer to the associated tile if the @p gid after this call is valid (wether it's modified or not)
        ///          Or nullptr if the final @p gid is invalid
        const TileType* updateAnimation(int &gid, entt::registry &registry, entt::entity e);

    private:
        const Tileset& m_tileset;

        /// Get the texture from an ID (texture's path)
        /// Load it if not already loaded
        const sf::Texture &cacheTexture(const std::string &id);

        /// "Pool" of textures
        /// Contains all the textures
        /// Load on the fly the needed textures from sprites
        /// key: the name of the file of the texture (relative path from the map file's directory)
        std::map<std::string, sf::Texture> m_texturesResource;
    };
}