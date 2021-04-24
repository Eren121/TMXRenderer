#include "tilemap/systems/PlayerMovementSystem.hpp"
#include "tilemap/Engine.hpp"

namespace Tm
{
    void PlayerMovementSystem::update()
    {
        if (!hasFocus())
        {
            return;
        }

        auto &movementSystem = m_engine.movementSystem();
        auto &region = m_engine.region();
        auto player = region.player();

        if (!movementSystem.isMoving(region, player))
        {
            const auto direction = m_sceneManager.controller().getInputVector();

            if (direction.x != 0 || direction.y != 0)
            {
                auto &playerPos = region.registry().get<Position>(player);
                auto destination = playerPos + direction;

                if (region.canMoveTo(destination))
                {
                    movementSystem.moveTo(region, player, destination);
                }
            }
        }
    }
}