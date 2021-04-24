#pragma once

#include "tilemap/Region.hpp"
#include "tilemap/System.hpp"

namespace Tm
{
    class PlayerMovementSystem : public System
    {
    public:
        using System::System;

        void update() override;
    };
}