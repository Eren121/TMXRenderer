#include "tilemap/Engine.hpp"
#include "tilemap/RegionLoader.hpp"
#include "config/Time.hpp"

namespace Tm
{
    Engine::Engine(renderer::SceneManager &sceneManager)
        : m_region(nullptr),
          m_movementSystem(nullptr),
          m_playerMovementSystem(nullptr)
    {
        static Tm::RegionLoader regionLoader("map.json");
        m_region = &regionLoader.region();

        m_movementSystem = new MovementSystem(sceneManager, *this);
        m_playerMovementSystem = new PlayerMovementSystem(sceneManager, *this);

        m_systems.emplace_back(m_movementSystem);
        m_systems.emplace_back(m_playerMovementSystem);
        m_systems.emplace_back(new InteractionSystem(sceneManager, *this));
    }

    void Engine::update()
    {
        if (m_region)
        {
            for (auto &system : m_systems)
            {
                system->update();
            }
        }
    }

    sf::Vector2f Engine::cameraPosition(const Region &region) const
    {
        const auto player = region.player();
        auto ret = m_movementSystem->getInterpolatedPosition(region, player);

        // The camera is always in the center of the player => center of the tile
        ret += 0.5f;

        return ret;
    }

    entt::entity Engine::player(const Region &region) const
    {
        auto view = region.registry().view<const Player>();
        for (auto entity : view)
        {
            return entity;
        }

        throw std::runtime_error("Player not found in region");
    }
}