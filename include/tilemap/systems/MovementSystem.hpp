#pragma once

#include "tilemap/System.hpp"
#include "tilemap/Region.hpp"

namespace Tm
{
    /**
     * @brief System that manage updating positions when an object is moving.
     * @remarks When you want to move a character, you have to ask this system.
     */
    class MovementSystem : public System
    {
    public:
        using System::System;
        void update() override;

        bool isMoving(const Region &region, entt::entity object) const;
        void moveTo(Region &region, entt::entity object, const vec2i &destination);

        /**
         * @return The "real" position of an object, for animating,
         *         that is reflecting the real position as float if it is moving.
         *         The standard integer position is returned if it is not moving.
         */
        vec2f getInterpolatedPosition(const Region &region, entt::entity object) const;
    };
}


