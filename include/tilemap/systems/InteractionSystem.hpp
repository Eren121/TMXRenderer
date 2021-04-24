#pragma once

#include "tilemap/System.hpp"

namespace Tm
{
    class InteractionSystem : public System
    {
    public:
        using System::System;

        /**
         * @brief Called when a player try to interact with a tile (a character, an object...) with clicking
         *        on associated command button.
         */
         void update() override;
    };
}

