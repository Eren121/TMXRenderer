#pragma once

#include <memory>
#include <entt/entt.hpp>
#include "Components.hpp"
#include "StaticLayer.hpp"

namespace Tm
{
    /**
     * Like a map in Pokemon (part loaded into the RAM)
     * (0, 0) = top left.
     */
    class Region
    {
    public:
        Region(int width, int height);
        Region(const sf::Vector2i &size);
        ~Region() = default;

        const sf::Vector2i size() const;

        /// Get the height of the region
        int height() const;
        /// Get the width of the region
        int width() const;

        /// Get the read-only registry of all objects of the region
        const entt::registry &registry() const;
        /// Get the registry of all objects of the region
        entt::registry &registry();

        bool hasPlayer() const;

        /**
         * @return The player entity. The player should exists in the region.
         */
        entt::entity player() const;

        /**
         * @return Wether a character can move to this position.
         * That means every layers allow moving to this position.
         */
        bool canMoveTo(const sf::Vector2i &tileCoords) const;

        const std::vector<StaticLayer>& layers() const;
        std::vector<StaticLayer>& layers();


    private:
        sf::Vector2i m_size;
        entt::registry m_registry;

        /// Ground of the region (static): water, grass, etc...
        std::vector<StaticLayer> m_layers;
    };
}