#pragma once

#include "Controller.hpp"
#include <SFML/Window.hpp>

class KeyboardController : public Controller
{
public:
    bool isPressed(Command command) const override;
    sf::Vector2<int> getInputVector() const override;

private:
    sf::Keyboard::Key convertCommandToKey(Command command) const;
};


