#include "config/Time.hpp"

sf::Time sf::getCurrentTime()
{
    static sf::Clock clock;
    return clock.getElapsedTime();
}
