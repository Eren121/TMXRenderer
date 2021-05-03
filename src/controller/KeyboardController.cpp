#include "controller/KeyboardController.hpp"

bool KeyboardController::isPressed(Command command) const
{
    return sf::Keyboard::isKeyPressed(convertCommandToKey(command));
}

sf::Keyboard::Key KeyboardController::convertCommandToKey(Command command) const
{
    sf::Keyboard::Key ret(sf::Keyboard::Unknown);

    switch (command)
    {
        case Command::LEFT: ret = sf::Keyboard::Left;
            break;

        case Command::RIGHT:
            ret = sf::Keyboard::Right;
            break;

        case Command::UP:
            ret = sf::Keyboard::Up;
            break;

        case Command::DOWN:
            ret = sf::Keyboard::Down;
            break;

        case Command::A:
            ret = sf::Keyboard::A;
            break;

        case Command::B:
            ret = sf::Keyboard::B;
            break;

        case Command::X:
            ret = sf::Keyboard::X;
            break;

        case Command::Y:
            ret = sf::Keyboard::Y;
            break;

        default:
            break;
    }

    return ret;
}

sf::Vector2<int> KeyboardController::getInputVector() const
{
    vec2i ret;

    if(!m_inputVectorStack.empty())
    {
        getInputDirection(m_inputVectorStack.top(), ret);
    }

    return ret;
}

bool KeyboardController::handleEvent(const sf::Event &e, Command &command)
{
    bool ret(false);
    
    switch (e.type)
    {
        case sf::Event::KeyPressed:
            ret = convertKeyToCommand(e.key.code, command);
            m_justPressedKeys.insert(e.key.code);
            break;

        case sf::Event::KeyReleased:
            {
                Command releasedCmd;
                if(convertKeyToCommand(e.key.code, releasedCmd))
                {
                    if(!m_inputVectorStack.empty() && m_inputVectorStack.top() == releasedCmd)
                    {
                        m_inputVectorStack.pop();

                        while(!m_inputVectorStack.empty() && !isPressed(m_inputVectorStack.top()))
                        {
                            m_inputVectorStack.pop();
                        }
                    }
                }
            }
            break;


        default:
            break;
    }

    if(ret)
    {
        // Update the input vector if key was pressed

        vec2i inputVec;
        if(getInputDirection(command, inputVec))
        {
            m_inputVectorStack.push(command);
        }
    }

    return ret;
}

void KeyboardController::frameStarted()
{
    m_justPressedKeys.clear();
}

bool KeyboardController::isJustPressed(Command command) const
{
    return m_justPressedKeys.contains(convertCommandToKey(command));
}

bool KeyboardController::convertKeyToCommand(sf::Keyboard::Key key, Command &command) const
{
    bool ret(true);

    switch(key)
    {
        default:
            ret = false;
            break;

        case sf::Keyboard::Left:
            command = Command::LEFT;
            break;

        case sf::Keyboard::Right:
            command = Command::RIGHT;
            break;

        case sf::Keyboard::Up:
            command = Command::UP;
            break;

        case sf::Keyboard::Down:
            command = Command::DOWN;
            break;

        case sf::Keyboard::A:
            command = Command::A;
            break;

        case sf::Keyboard::B:
            command = Command::B;
            break;

        case sf::Keyboard::X:
            command = Command::X;
            break;

        case sf::Keyboard::Y:
            command = Command::Y;
            break;
    }

    return ret;
}

void KeyboardController::markAsConsumed(Command command)
{
    m_justPressedKeys.erase(convertCommandToKey(command));
}
