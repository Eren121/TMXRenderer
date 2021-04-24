#pragma once

#include "common.hpp"
#include "pokemon/MoveSlot.hpp"

namespace Btl
{
    /// AI for a battle.
    /// Has to play the best to win a battle.
    /// Or play very bad if the AI is easy to adapt for him (lol).
    class BattleAI
    {
    public:
        virtual ~BattleAI() = default;

        /// Choose the next non-ko pokemon to enter the battle and be the king of the battle.
        virtual entt::entity choosePokemon(const entt::registry&, const std::vector<entt::entity>& pokemonsBasket) = 0;

        /// Choose the attack for next turn.
        virtual const Pkm::MoveSlot& chooseMove(const entt::registry&, entt::entity pokemon) = 0;
    };
}