#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

class Iterator2D;

namespace sf
{
    Iterator2D begin(const sf::IntRect &rect);
    Iterator2D end(const sf::IntRect &rect);
}

/// Simple iteration over 2D array with incrementation
/// Order is first dimension first and then second dimension
/// Example:
/// @code
/// Iterator2D it(2, 2);
/// vec2i pos;
/// pos = *it; ++it; // pos == (0, 0)
/// pos = *it; ++it; // pos == (1, 0)
/// pos = *it; ++it; // pos == (0, 1)
/// pos = *it; ++it; // pos == (1, 1)
/// @endcode
class Iterator2D
{
public:
    explicit Iterator2D(const sf::Vector2i &size, const sf::Vector2i &origin = {0, 0});
    explicit Iterator2D(const sf::IntRect &rect);

    sf::Vector2i operator*() const;

    /// Preincrement
    Iterator2D &operator++();

    /// @remarks Only compare the relative position
    ///          Sufficient for range-based loop
    bool operator!=(const Iterator2D &rhs) { return m_currentRelativeLoc != rhs.m_currentRelativeLoc; }

private:
    sf::Vector2i m_origin;
    sf::Vector2i m_size;

    /// Current location relative to (0, 0)
    /// (and not the origin)
    /// Add to origin to get the real location
    /// 0 1 2
    /// 3 4 5
    /// 6 7 8
    int m_currentRelativeLoc;

    friend Iterator2D sf::begin(const sf::IntRect &rect);
    friend Iterator2D sf::end(const sf::IntRect &rect);
};

inline Iterator2D sf::begin(const sf::IntRect &rect)
{
    return Iterator2D(rect);
}

inline Iterator2D sf::end(const sf::IntRect &rect)
{
    Iterator2D ret(rect);

    // Last position is bottom right corner +1 equals to width * height
    ret.m_currentRelativeLoc = rect.width * rect.height;

    return ret;
}