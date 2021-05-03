#include "tilemap/systems/MovementSystem.hpp"
#include "tilemap/Engine.hpp"

namespace Tm
{
    void MovementSystem::update()
    {
        auto &region = m_engine.region();
        auto &registry = region.registry();
        auto view = registry.view<IsMoving, Character, Position>();

        for (auto &&[entity, moving, character, pos] : view.each())
        {
            // Stop moving & update position if time is reached
            const float adv = ((sf::getCurrentTime() - moving.startingTime) / character.speed);
            const bool reachedDestination = (adv >= 1.0f);

            if (reachedDestination)
            {
                // Update accordingly the object's position
                pos = moving.destination;

                // Removing the IsMoving component so that the object does not move anymore
                registry.remove<IsMoving>(entity);
            }
            else
            {
                // Update position interpolating destination and origin
                // Note: do not re-calculate at each ask of the position and cache it,
                // because in this case the position
                // could change inside the same frame and cause visual glitches

                moving.interpolatedPos = interpolation::linear<vec2f>(pos, moving.destination, adv);
            }
        }
    }

    bool MovementSystem::isMoving(const Region &region, entt::entity object) const
    {
        return region.registry().has<IsMoving>(object);
    }

    void MovementSystem::moveTo(Region &region, entt::entity object, const vec2i &destination)
    {
        if (!region.registry().has<IsMoving>(object))
        {
            auto &pos = region.registry().get<Position>(object);
            region.registry().emplace<IsMoving>(object, destination, pos);
        }
    }

    vec2f MovementSystem::getInterpolatedPosition(entt::entity object) const
    {
        const auto &registry = m_engine.region().registry();
        const auto &moving = registry.try_get<IsMoving>(object);
        const auto &currentPos = registry.get<Position>(object);
        vec2f ret;

        if (moving)
        {
            ret = moving->interpolatedPos;
        }
        else
        {
            ret = vec2f(currentPos);
        }

        return ret;
    }
}