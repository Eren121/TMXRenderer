#pragma once

#include "Layer.hpp"

namespace Tm
{
    class Region;

    /// Entities within this layers will be rendered with the same
    /// Z-index of their layer (as if it was tile layers)
    class LayerOfObjects
        : public Layer
    {
    public:
        explicit LayerOfObjects(Region &region);
        ~LayerOfObjects() override = default;

        /// @returns true if there is no dynamic entity in this position
        bool canMoveTo(const sf::Vector2i &pos) const override;

        /// @remarks Same as canMoveTo()
        bool isTileEmpty(const sf::Vector2i &pos) const override;

        void render(sf::RenderTarget &target, TileRenderer &renderer, const sf::IntRect &bounds,
                    const sf::Transform &parentTransform) const override;

        /// Add an entity in this layer
        void addEntity(entt::entity entity);

    private:
        /// Entities at this layer
        std::vector<entt::entity> m_entities;
        entt::registry &m_registry;
    };
}