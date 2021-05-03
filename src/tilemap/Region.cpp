#include "tilemap/Region.hpp"
#include "tilemap/Layer.hpp"
#include <algorithm>

namespace Tm
{
    Region::Region(int width, int height)
        : Region(sf::Vector2i{width, height})
    {

    }

    Region::Region(const sf::Vector2i &size)
        : m_size(size)
    {

    }

    const sf::Vector2i Region::size() const
    {
        return m_size;
    }

    int Region::width() const
    {
        return m_size.x;
    }

    int Region::height() const
    {
        return m_size.y;
    }

    bool Region::hasPlayer() const
    {
        const auto view = m_registry.view<const Player>().each();
        return view.begin() != view.end();
    }

    const entt::registry &Region::registry() const
    {
        return m_registry;
    }

    entt::registry &Region::registry()
    {
        return m_registry;
    }

    entt::entity Region::player() const
    {
        auto view = m_registry.view<const Player>();
        for (auto entity : view)
        {
            return entity;
        }

        assert("Not player found while getting the player" && false);
    }

    bool Region::canMoveTo(const sf::Vector2i &tileCoords) const
    {
        bool ret(false);

        // Check for OOB
        if (tileCoords.x >= 0 && tileCoords.y >= 0 && tileCoords.x < width() && tileCoords.y < height())
        {
            ret = true;

            // Can move only if all layers allow moving to this position

            // Previously checked for "there is at least one non-empty layer"
            // But supposely there is always at last one non-empty layer in fact (otherwise black background)

            for (const auto &layer : m_layers)
            {
                if (!layer->canMoveTo(tileCoords))
                {
                    ret = false;
                    break;
                }
            }
        }

        return ret;
    }
}
