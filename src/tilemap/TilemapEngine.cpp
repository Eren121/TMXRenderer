#include "tilemap/TilemapEngine.hpp"
#include "config/Time.hpp"

namespace Tm
{
    TilemapEngine::TilemapEngine(Controller &controller)
        : m_controller(controller),
          m_moveDuration(sf::milliseconds(200))
    {
    }

    void TilemapEngine::setController(Controller &controller)
    {
        m_controller = controller;
    }

    void TilemapEngine::update(Tm::Region &region)
    {
        updatePlayerMove(region);
    }

    void TilemapEngine::updatePlayerMove(Region &region)
    {
        if (!isMoving())
        {
            const auto direction = m_controller.getInputVector();

            if (direction.x != 0 || direction.y != 0)
            {
                auto player = region.player();
                auto &playerPos = region.registry().get<Tm::Position>(player);

                if (region.canMoveTo(playerPos + direction))
                {
                    m_previousPlayerPos = playerPos;
                    m_lastMoveTime = sf::getCurrentTime();

                    playerPos += direction;
                    cout << "Moves to " << playerPos << endl;
                }
            }
        }
    }

    sf::Vector2f TilemapEngine::getPlayerMovingPosition(const Region &region) const
    {
        const auto playerID = region.player();
        const auto currentPos = sf::Vector2f(region.registry().get<Tm::Position>(playerID));
        sf::Vector2f ret;

        if (isMoving())
        {
            // Moving advancement (0.0 to 1.0)
            const float adv = (sf::getCurrentTime() - m_lastMoveTime) / m_moveDuration;
            ret = sf::Vector2f(m_previousPlayerPos) * (1.0f - adv) + currentPos * adv;
        }
        else
        {
            ret = currentPos;
        }

        return ret;
    }

    bool TilemapEngine::isMoving() const
    {
        return (sf::getCurrentTime() - m_lastMoveTime < m_moveDuration);
    }
}