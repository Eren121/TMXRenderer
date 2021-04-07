#pragma once

#include <SFML/System.hpp>

namespace sf
{
    /**
     * @return The time from an arbitrary point in time. The point is the same across all calls of this function.
     */
    sf::Time getCurrentTime();
}