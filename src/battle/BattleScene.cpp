#include "battle/BattleScene.hpp"
#include "battle/InitState.hpp"
#include "tilemap/Components.hpp"

using namespace std;
using namespace sf;

namespace Btl
{
    BattleScene::BattleScene(renderer::SceneManager& parent, entt::registry& registry, entt::entity opponent)
        : Scene(parent),
          m_state(std::make_unique<InitState>(*this)),
          m_registry(registry),
          m_opponent(opponent)
    {
        m_player = getSingletonEntity<Tm::Player>(registry);
    }

    bool BattleScene::handleCommand(Command command)
    {
        return m_state->handleCommand(command);
    }

    void BattleScene::renderScene()
    {
        renderHealthBars();

        m_state->render();
    }

    bool BattleScene::isOpaque() const
    {
        return true;
    }

    void BattleScene::update()
    {
        auto newState = m_state->update();
        if(newState)
        {
            m_state = std::move(newState);
        }
    }

    void BattleScene::renderHealthBars()
    {
        RectangleShape healthBar;

        // Render opponent health bar
        healthBar.setPosition({0.1f, 0.1f});
        healthBar.setSize({0.5f, 0.02f});
        healthBar.setFillColor(Color::White);

        window().draw(healthBar, m_coordSystem);

        // Render player heath bar
        healthBar.setPosition({0.4f, 0.6f});
        window().draw(healthBar, m_coordSystem);
    }
}