#pragma once

#include "TileType.hpp"
#include "TileRenderer.hpp"
#include "common.hpp"

namespace Tm
{
    class Engine;

    /**
     * @brief One layer of the region.
     * A region is composed of multiple layers:
     *  - One layer of ground (static)
     *  - One layer of decoration object (static)
     *  - One layer of characters, moveable objects (dynamic)
     *
     *  Tiled have separate layers for objects and tiles.
     *  That mean that either a layer is composed of static tiles or of dynamic ones.
     *  As we need to render dynamic objects (like characters or the player)
     *  also with a Z-index, the objects reminds in which layer they where
     *  positioned.
     */
    class Layer
    {
    public:
        Layer(const sf::Vector2i &size);
        virtual ~Layer() = default;

        const vec2i &size() const { return m_size; }

        int width() const;
        int height() const;

        /// @param pos The position to check.
        virtual bool isTileEmpty(const sf::Vector2i &pos) const = 0;

        /// @return Wether a character can be placed at this position:
        virtual bool canMoveTo(const sf::Vector2i &tileCoords) const = 0;

        /// Name of the layer as in Tiled Editor
        auto &name() const { return m_name; }

        void setName(const string &name) { m_name = name; }


        /// @brief Render a layer
        /// @params bounds Render only in bounds to optimize, because the camera don't see the entire map
        /// @remarks The rendering is done in world coordinates
        virtual void render(sf::RenderTarget &target, TileRenderer &renderer, const sf::IntRect &bounds,
                            const sf::Transform &parentTransform) const = 0;

        void setEngine(const Tm::Engine& engine) { m_engine = &engine; }

        tmx::Layer::Type type() const { return m_type; }

    protected:
        tmx::Layer::Type m_type;
        sf::Vector2i m_size;
        string m_name;

        const Tm::Engine* m_engine{nullptr};
    };
}