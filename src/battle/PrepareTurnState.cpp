#include "battle/PrepareTurnState.hpp"
#include "battle/BattleScene.hpp"

namespace Btl
{
    Btl::PrepareTurnState::PrepareTurnState(Btl::BattleScene& scene)
        : State(scene),
          m_turnMenu(scene.parent(), {2, 2})
    {
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

    std::unique_ptr<State> Btl::PrepareTurnState::update()
    {
        return nullptr;
    }

    void PrepareTurnState::render()
    {
        m_scene.window().draw(m_turnMenu, m_scene.coordSystem());
    }

    void PrepareTurnState::receiveEvent(const ui::OnOptionAccept& eventData)
    {
        const auto& btn = eventData.choice;

        if (btn == BTN_CHOOSE_FLEE)
        {
             m_scene.close();
        }
    }

    bool PrepareTurnState::handleCommand(Command command)
    {
        return m_turnMenu.handleCommand(command);
    }
}