#pragma once

#include "BattleAI.hpp"

namespace Btl
{
    /// An AI that makes all decisions randomly.
    class RandomAI : public BattleAI
    {
    public:
        const Pkm::MoveSlot &chooseMove(const entt::registry &, entt::entity pkmEntity) override;
        entt::entity choosePokemon(const entt::registry &, const std::vector<entt::entity> &pkmBasket) override;
    };
}