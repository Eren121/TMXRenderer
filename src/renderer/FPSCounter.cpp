#include "renderer/FPSCounter.hpp"

namespace renderer
{

    FPSCounter::FPSCounter()
        : m_framesCount(0), m_start()
    {

    }

    bool FPSCounter::notifyOneFrame(float &fps)
    {
        bool ret(false);

        m_framesCount++;

        if (m_start.getElapsedTime() > sf::seconds(1.0f))
        {
            ret = true;
            fps = float(m_framesCount) / m_start.restart().asSeconds();
            m_framesCount = 0;
        }

        return ret;
    }
}