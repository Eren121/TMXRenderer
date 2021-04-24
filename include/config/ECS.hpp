/// entt utilities

#pragma once

#include <entt/entt.hpp>

namespace entt
{
    /// A Singleton Component is a component that exists only once in the entire world.
    /// For example the Player.
    /// Get the entity associated with this component.
    /// Throw out_of_range if the component does not exists.
    template<typename Component>
    entt::entity getSingletonEntity(const entt::registry& registry)
    {
        auto view = registry.view<const Component>();
        for(auto entity : view)
        {
            // Returns the first entity
            // Therre should be only one
            return entity;
        }

        throw std::out_of_range("Singleton Component not found in registry");
    }
}