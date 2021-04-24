#pragma once

#include <string>
#include <iostream>
#include <SFML/Math.hpp>
#include <SFML/Graphics/Rect.hpp>

using std::cout;
using std::endl;

namespace sf
{
    template<typename T>
    sf::Vector2<T> floor(const sf::Vector2<T> &vector)
    {
        using std::floor;
        sf::Vector2<T> ret;
        ret.x = floor(vector.x);
        ret.y = floor(vector.y);
        return ret;
    }

    template<typename T>
    sf::Vector2<T> ceil(const sf::Vector2<T> &vector)
    {
        using std::ceil;
        sf::Vector2<T> ret;
        ret.x = ceil(vector.x);
        ret.y = ceil(vector.y);
        return ret;
    }

    template<typename T>
    sf::Vector2<T> min(const sf::Vector2<T> &vector1, const sf::Vector2<T> &vector2)
    {
        using std::min;
        sf::Vector2<T> ret;
        ret.x = min(vector1.x, vector2.x);
        ret.y = min(vector1.y, vector2.y);
        return ret;
    }

    template<typename T>
    sf::Vector2<T> max(const sf::Vector2<T> &vector1, const sf::Vector2<T> &vector2)
    {
        using std::max;
        sf::Vector2<T> ret;
        ret.x = max(vector1.x, vector2.x);
        ret.y = max(vector1.y, vector2.y);
        return ret;
    }

    template<typename T>
    sf::Vector2<T> clamp(const sf::Vector2<T> &value, const sf::Vector2<T>& low, const sf::Vector2<T> high)
    {
        using std::clamp;
        sf::Vector2<T> ret;
        ret.x = clamp(value.x, low.x, high.x);
        ret.y = clamp(value.y, low.y, high.y);
        return ret;
    }
}

template<typename T>
std::vector<std::vector<T>> create2DVector(int dim1, int dim2)
{
    std::vector<std::vector<T>> ret;

    ret.resize(dim1);
    for (int i = 0; i < dim1; ++i)
    {
        ret[i].resize(dim2);
    }

    return ret;
}

template<typename T>
std::vector<std::vector<T>> create2DVector(const sf::Vector2i &size)
{
    return create2DVector<T>(size.x, size.y);
}

template<typename T> using vec2 = sf::Vector2<T>;
using vec2f = vec2<float>;
using vec2i = vec2<int>;

template<typename T>
T clamp(T x, T min, T max)
{
    return x < min ? min : x > max ? max : x;
}

/// Returns wheter the point is inside the rect (0, 0) -> @p size
/// The rect is defined as (0, 0) included and @p size is excluded
/// The U stand for "unsigned" because the origin is (0, 0) so always positive
template<typename T>
bool insideURect(const sf::Vector2<T> &size, const sf::Vector2<T> &point)
{
    return point.x >= 0 && point.y >= 0             // Check positive
           && point.x < size.x && point.y < size.y;    // Check inside rect
}

template<typename T>
sf::Vector2<T> rectSize(const sf::Rect<T> &rect)
{
    return {rect.width, rect.height};
}

template<typename T>
bool operator<(const sf::Vector2<T> &rhs, const sf::Vector2<T> &lhs)
{
    return rhs.x < lhs.x || (rhs.x == lhs.x && rhs.y < lhs.y);
}

struct vec_comp
{
    template<typename T>
    bool operator()(const sf::Vector2<T> &rhs, const sf::Vector2<T> &lhs) const
    {
        return rhs.x < lhs.x || (rhs.x == lhs.x && rhs.y < lhs.y);
    }
};