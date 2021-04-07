#pragma once

#include <SFML/System.hpp>

/**
 * @brief All related to player inputs.
 */
class Controller
{
public:
    /**
     * @brief All commands. As the game can be played on a console, there is few commands.
     *        On keyboard, each one could be just a key.
     */
    enum Command
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    virtual bool isPressed(Command command) const = 0;

    /**
     * @brief Facilitates the use of directions. The vector returned is always unit in one direction.
     * @remarks If multiple direction are pressed, it always return only one direction choosen arbitrarly,
     *          but in consistent order.
     * @remarks Origin is like in most window engine: from top left corner to bottom right corner.
     * @example If LEFT command is pressed, then return (1, 0).
     * @return The direction of the command pressed, or (0, 0) if no direction command is pressed.
     */
    virtual sf::Vector2<int> getInputVector() const = 0;
};


