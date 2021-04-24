#pragma once

#include "Region.hpp"
#include "tilemap/systems/MovementSystem.hpp"
#include "tilemap/systems/PlayerMovementSystem.hpp"
#include "tilemap/systems/InteractionSystem.hpp"
#include "renderer/SceneManager.hpp"

namespace Tm
{
    class Engine
    {
    public:
        Engine(renderer::SceneManager &sceneManager);
        ~Engine() = default;

        void update();

        /// @returns The position of the player with decimal corresponding if he is moving
        /// @remarks If the player is not moving, returns his normal position.
        /// @remarks If the player is moving, returns an interpolation between his old and new positions.
        sf::Vector2f cameraPosition(const Region &region) const;

        const MovementSystem &movementSystem() const { return *m_movementSystem; }

        MovementSystem &movementSystem() { return *m_movementSystem; }

        entt::entity player(const Region &region) const;

        Region &region() { return *m_region; }

        const Region &region() const { return *m_region; }

    private:
        Region *m_region;
        MovementSystem *m_movementSystem;
        PlayerMovementSystem *m_playerMovementSystem;
        std::vector<UniquePtr<System>> m_systems;
    };

}