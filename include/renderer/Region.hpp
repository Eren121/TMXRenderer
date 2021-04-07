#pragma once

#include "tilemap/Region.hpp"

namespace renderer
{
    class Region
    {
    public:
        virtual ~Region() = default;

        virtual void render(const Tm::Region &region) = 0;
    };
}
