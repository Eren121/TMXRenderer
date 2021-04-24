#pragma once

#include "common.hpp"
#include "battle/BattleAI.hpp"
#include "battle/RandomAI.hpp"

namespace Pkm
{
    /**
     * @brief A trainer is a character who has pokemons and can battle.
     * @remarks Do not store name because it is stored in a more generic component.
     */
    struct Trainer
    {
        /// The pokemons the trainer has on him
        std::vector<entt::entity> pokemons;

        /// The AI for battle for this trainer
        /// UniquePtr so can use of polymorphism without managing the memory.
        /// We don't use components for strategy because we need different possibles strategies for battle,
        /// So polymorphism is adapted.
        UniquePtr<Btl::BattleAI> battleAI = std::make_unique<Btl::RandomAI>();
    };
}