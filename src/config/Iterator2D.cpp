#include "config/Iterator2D.hpp"

Iterator2D::Iterator2D(const sf::Vector2i &size, const sf::Vector2i &origin)
    : m_origin(origin),
      m_size(size),
      m_currentRelativeLoc(0)
{
}

Iterator2D::Iterator2D(const sf::IntRect &rect)
    : m_origin(rect.left, rect.top),
      m_size(rect.width, rect.height),
      m_currentRelativeLoc(0)
{
}

sf::Vector2i Iterator2D::operator*() const
{
    // Convert 1D to 2D
    const int x = m_currentRelativeLoc % m_size.x;
    const int y = m_currentRelativeLoc / m_size.x;

    sf::Vector2i ret;
    ret.x = m_origin.x + x;
    ret.y = m_origin.y + y;

    return ret;
}

Iterator2D &Iterator2D::operator++()
{
    ++m_currentRelativeLoc;
    return *this;
}