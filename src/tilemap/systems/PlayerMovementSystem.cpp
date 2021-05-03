#include "tilemap/systems/PlayerMovementSystem.hpp"
#include "tilemap/Engine.hpp"
#include "config/Debug.hpp"

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
                
                if (debugState.noCollisions || region.canMoveTo(destination))
                {
                    movementSystem.moveTo(region, player, destination);
                }

                // Update facing direction accordingly to the move direction
                // Even if the player do not actually move
                auto &character = region.registry().get<Character>(player);
                const auto &pos = region.registry().get<Tm::Position>(player);
                character.facingDirection = facingDirection(destination - pos);
            }
        }
    }
}