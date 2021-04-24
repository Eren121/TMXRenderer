#include "battle/RandomAI.hpp"
#include "pokemon/Pokemon.hpp"

using namespace std;
using namespace sf;

namespace Btl
{
    entt::entity
    RandomAI::choosePokemon(const entt::registry &registry, const std::vector<entt::entity> &pkmBasket)
    {
        // Filter all non-KO pokemons
        auto nonKOs = filter(pkmBasket, [&](auto pkmEntity) {
            return Pkm::isKO(registry, pkmEntity);
        });

        // Get one random pokemon from the vector filtered
        auto &randomPkm = randomElement(nonKOs);

        // Return it
        return randomPkm;
    }

    const Pkm::MoveSlot &RandomAI::chooseMove(const entt::registry &registry, entt::entity pkmEntity)
    {
        auto pokemon = registry.get<Pkm::Pokemon>(pkmEntity);

        // Filter all moves with remaining PPs
        auto remainingMoves = filter(pokemon.moveSlots, Pkm::hasPP);

        // Get one move at random
        auto &randomMove = randomElement(remainingMoves);

        // Return it
        return randomMove;
    }
}