#pragma once

#include <string>
#include <iostream>
#include <SFML/System.hpp>

using std::cout;
using std::endl;

namespace sf
{

#define DEFINE_SF_VECTOR2_OPERATOR(op) \
        template<typename T> \
        sf::Vector2<T> operator op(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs) { \
            return {lhs.x op rhs.x, lhs.y op rhs.y}; \
        }

    /**
     * @brief Generic definition of operator with a primitive, treated like a vector with same component in X and Y.
     */
#define DEFINE_SF_VECTOR2_OPERATOR_1D(op) \
        template<typename T> \
        sf::Vector2<T> operator op(const sf::Vector2<T>& lhs, T rhs) { \
            return {lhs.x op rhs, lhs.y op rhs}; \
        }

    DEFINE_SF_VECTOR2_OPERATOR(*)

    DEFINE_SF_VECTOR2_OPERATOR(/)

    DEFINE_SF_VECTOR2_OPERATOR_1D(+)

    template<typename T>
    std::string to_string(const sf::Vector2<T> &v)
    {
        using std::to_string;
        return "(" + to_string(v.x) + ", " + to_string(v.y) + ")";
    }

    template<typename T>
    std::string to_string(const sf::Vector3<T> &v)
    {
        using std::to_string;
        return "(" + to_string(v.x) + ", " + to_string(v.y) + ", " + to_string(v.z) + ")";
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &lhs, const sf::Vector2<T> &rhs)
    {
        lhs << to_string(rhs) << endl;
        return lhs;
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