#include "controller/KeyboardController.hpp"

bool KeyboardController::isPressed(Controller::Command command) const
{
    return sf::Keyboard::isKeyPressed(convertCommandToKey(command));
}

sf::Keyboard::Key KeyboardController::convertCommandToKey(Controller::Command command) const
{
    sf::Keyboard::Key ret(sf::Keyboard::Unknown);

    switch (command)
    {
        case LEFT:
            ret = sf::Keyboard::Left;
            break;

        case RIGHT:
            ret = sf::Keyboard::Right;
            break;

        case UP:
            ret = sf::Keyboard::Up;
            break;

        case DOWN:
            ret = sf::Keyboard::Down;
            break;

        default:
            break;
    }

    return ret;
}

sf::Vector2<int> KeyboardController::getInputVector() const
{
    sf::Vector2<int> ret;

    if(isPressed(LEFT))
    {
        ret.x--;
    }
    else if(isPressed(RIGHT))
    {
        ret.x++;
    }
    else if(isPressed(UP))
    {
        ret.y--;
    }
    else if(isPressed(DOWN))
    {
        ret.y++;
    }

    return ret;
}
