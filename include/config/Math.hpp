#pragma once

#include <string>
#include <iostream>
#include <SFML/Math.hpp>
#include <SFML/Graphics/Rect.hpp>

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

/// Returns wheter the point is inside the rect (0, 0) -> @p size
/// The rect is defined as (0, 0) included and @p size is excluded
template<typename T>
bool isInsideRect(const sf::Vector2<T> &size, const sf::Vector2<T> &point)
{
    return point.x >= 0 && point.y >= 0             // Check positive
           && point.x < size.x && point.y < size.y;    // Check inside rect
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