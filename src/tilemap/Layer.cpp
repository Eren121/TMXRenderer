
#include "tilemap/AbstractLayer.hpp"

namespace Tm
{
    AbstractLayer::AbstractLayer(const sf::Vector2i &size)
        : m_size(size),
          m_scroll(1.0f, 1.0f)
    {

    }

    int AbstractLayer::width() const
    {
        return m_size.x;
    }

    int AbstractLayer::height() const
    {
        return m_size.y;
    }
}
