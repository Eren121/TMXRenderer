#include "battle/BattleScene.hpp"
#include "tilemap/Components.hpp"

using namespace std;
using namespace sf;

namespace Btl
{
    BattleScene::BattleScene(renderer::SceneManager &parent, entt::registry &registry, entt::entity opponent)
        : Scene(parent),
          m_registry(registry),
          m_opponent(opponent),
          m_turnMenu(parent, {2, 2})
    {
        m_player = getSingletonEntity<Tm::Player>(registry);

        const auto border = 0.01f;
        const auto posY = 0.75f;

        m_turnMenu.setPosition({border, posY});
        m_turnMenu.setScale({1.0f - border * 2.0f, 1.0f - posY - border});

        m_turnMenu.setLabel(BTN_CHOOSE_MOVE, "Move");
        m_turnMenu.setLabel(BTN_CHOOSE_OBJ, "Object");
        m_turnMenu.setLabel(BTN_CHOOSE_PKM, "Pokemons");
        m_turnMenu.setLabel(BTN_CHOOSE_FLEE, "Flee");

        m_turnMenu.attachObserver(*this);
    }

    bool BattleScene::handleCommand(Command command)
    {
        cout << command << endl;
        m_turnMenu.handleCommand(command);
        return true;
    }

    void BattleScene::renderScene()
    {
        window().draw(m_turnMenu, m_coordSystem);
        renderHealthBars();
    }

    bool BattleScene::isOpaque() const
    {
        return true;
    }

    void BattleScene::update()
    {
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

    void BattleScene::receiveEvent(const ui::OnOptionAccept &eventData)
    {
        const auto& btn = eventData.choice;

        if(btn == BTN_CHOOSE_FLEE)
        {
            close();
        }
    }
}