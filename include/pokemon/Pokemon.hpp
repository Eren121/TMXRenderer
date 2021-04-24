#pragma once

#include "MoveSlot.hpp"

namespace Pkm
{
    /**
     * @brief Main component of pokemons.
     * A pokemon has:
     *  - a name
     *  - a current life / a max. life (KO when life is zero)
     *  - attack
     *  - defense
     *  - multiple attacks: in many pokemons, only 4 max.
     */
    struct Pokemon
    {
        string name;
        int life;
        int maxLife;
        int atk;
        int def;
        int speed;
        std::vector<MoveSlot> moveSlots;
    };

    /// A pokemon is K.O. When his life is equals to zero.
    bool isKO(const Pokemon &pokemon);

    /// If the entity is not a pokemon, returns false.
    bool isKO(const entt::registry &registry, entt::entity pkmEntity);
}