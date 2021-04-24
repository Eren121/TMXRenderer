#include "pokemon/MoveSlot.hpp"

namespace Pkm
{
    bool hasPP(const MoveSlot &slot)
    {
        return slot.currentPP > 0;
    }
}
