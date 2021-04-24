#pragma once

#include "common.hpp"
#include "Move.hpp"

namespace Pkm
{
    /**
     * @brief Unique per move per pokemon to store the current PP.
     * @remarks Not a component.
     */
    struct MoveSlot
    {
        const Move *move;
        int currentPP;
    };

    /// @returns true if the pokemon can use the move because there is available PPs (pps > 0).
    bool hasPP(const MoveSlot &slot);
}