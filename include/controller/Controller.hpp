#pragma once

#include "Command.hpp"
#include <SFML/System.hpp>
#include <SFML/Window/Event.hpp>

namespace renderer {
    class SceneManager;
}

/**
 * @brief All related to player inputs.
 */
class Controller
{
public:
    Controller() = default;
    virtual ~Controller() = default;

    virtual bool isPressed(Command command) const = 0;
    virtual bool isJustPressed(Command command) const = 0;

    /**
     * @brief Facilitates the use of directions. The vector returned is always unit in one direction.
     * @remarks If multiple direction are pressed, it always return only one direction choosen arbitrarly,
     *          but in consistent order.
     * @remarks Origin is like in most window engine: from top left corner to bottom right corner.
     *          In World Space.
     * @example If LEFT command is pressed, then return (1, 0).
     * @return The direction of the command pressed, or (0, 0) if no direction command is pressed.
     */
    virtual sf::Vector2<int> getInputVector() const = 0;

    virtual bool handleEvent(const sf::Event &e, Command &command) = 0;
    virtual void frameStarted() = 0;

    virtual void markAsConsumed(Command command) = 0;
};


