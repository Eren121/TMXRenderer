#pragma once

#include "Region.hpp"
#include "controller/Controller.hpp"

namespace Tm
{
    class TilemapEngine
    {
    public:
        TilemapEngine(Controller &controller);
        ~TilemapEngine() = default;

        void update(Region &region);

        void setController(Controller &controller);

        bool isMoving() const;

        /// @returns The position of the player with decimal corresponding if he is moving
        /// @remarks If the player is not moving, returns his normal position.
        /// @remarks If the player is moving, returns an interpolation between his old and new positions.
        sf::Vector2f getPlayerMovingPosition(const Region &region) const;

    private:
        /**
         * @brief Update the player position if he ask to move and can move.
         */
        void updatePlayerMove(Region &region);

    private:
        /// The controller used for input in this engine.
        Controller &m_controller;

        /// The last time the player has entered a move command.
        sf::Time m_lastMoveTime;

        /// The previous position of the player before a move
        sf::Vector2i m_previousPlayerPos;

        /**
         * @brief The duration to move from one tile to another.
         * @remark Define the speed of the player.
         */
        sf::Time m_moveDuration;
    };

}