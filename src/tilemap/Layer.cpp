
#include "tilemap/Layer.hpp"

namespace Tm
{
    Layer::Layer(const sf::Vector2i &size)
        : m_size(size),
          m_scroll(1.0f, 1.0f)
    {

    }

    int Layer::width() const
    {
        return m_size.x;
    }

    int Layer::height() const
    {
        return m_size.y;
    }
}
