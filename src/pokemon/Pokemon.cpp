#include <pokemon/Pokemon.hpp>

namespace Pkm
{
    bool isKO(const Pokemon &pokemon)
    {
        return pokemon.life <= 0;
    }

    bool isKO(const entt::registry &registry, entt::entity pkmEntity)
    {
        bool ret(false);

        if (auto pokemon = registry.try_get<Pokemon>(pkmEntity))
        {
            ret = isKO(*pokemon);
        }

        return ret;
    }
}
