#pragma once

#include <set>
#include "common.hpp"
#include "Controller.hpp"
#include "renderer/SceneManager.hpp"

class KeyboardController : public Controller
{
public:
    bool isPressed(Command command) const override;
    bool isJustPressed(Command command) const override;
    vec2i getInputVector() const override;

    bool handleEvent(const sf::Event &e, Command &command) override;
    void frameStarted() override;

private:
    sf::Keyboard::Key convertCommandToKey(Command command) const;
    bool convertKeyToCommand(sf::Keyboard::Key key, Command &command) const;
public:
    void markAsConsumed(Command command) override;
private:
    std::set<sf::Keyboard::Key> m_justPressedKeys;

    std::stack<Command> m_inputVectorStack;
};


