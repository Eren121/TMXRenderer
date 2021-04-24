#pragma once

#include "common.hpp"

namespace renderer
{
    class FPSCounter final
    {
    public:
        FPSCounter();
        ~FPSCounter() = default;

        /**
         * @param fps To store the fps. Changed only if returns true.
         * @return true If fps has be measured since 1 second
         */
        bool notifyOneFrame(float &fps);

    private:

        /// Total frame count accumulation
        int m_framesCount;

        /// Clock starting when m_framesCount = 0 (when the fps counter is reseted)
        sf::Clock m_start;
    };
}


