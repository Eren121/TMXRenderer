#include "tilemap/Region.hpp"
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

        assert(false);
    }

    bool Region::canMoveTo(const sf::Vector2i &tileCoords) const
    {
        bool ret(false);

        if (tileCoords.x >= 0 && tileCoords.y >= 0 && tileCoords.x < width() && tileCoords.y < height())
        {
            bool empty(true);
            ret = true;


            // Can move only if there is at least one non-empty layer
            // And all non-empty layers allow moving to this position

            for (auto &layer : m_layers)
            {
                if (layer.contains(tileCoords))
                {
                    empty = false;

                    if (!layer.canMoveTo(tileCoords))
                    {
                        ret = false;
                        break;
                    }
                }
            }

            if (empty)
            {
                ret = false;
            }
        }

        return ret;
    }

    const std::vector<StaticLayer> &Region::layers() const
    {
        return m_layers;
    }

    std::vector<StaticLayer> &Region::layers()
    {
        return m_layers;
    }
}
