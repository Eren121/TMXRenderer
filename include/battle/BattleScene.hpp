#pragma once

#include "renderer/Scene.hpp"
#include "renderer/SceneManager.hpp"
#include "ui/MenuWidget.hpp"

namespace Btl
{
    class BattleScene
        : public renderer::Scene,
          public obs::Observer<ui::OnOptionAccept>
    {
    public:
        BattleScene(renderer::SceneManager &parent, entt::registry &registry, entt::entity opponent);

        bool isOpaque() const override;
        void renderScene() override;
        void update() override;
        bool handleCommand(Command command) override;

        void receiveEvent(const ui::OnOptionAccept &eventData) override;

    protected:
        void renderHealthBars();


    private:
        entt::registry &m_registry;
        entt::entity m_opponent;
        entt::entity m_player;

        /// Menu for turn action
        ui::MenuWidget m_turnMenu;

        static inline const vec2i BTN_CHOOSE_MOVE = {0, 0};
        static inline const vec2i BTN_CHOOSE_PKM = {0, 1};
        static inline const vec2i BTN_CHOOSE_OBJ = {1, 0};
        static inline const vec2i BTN_CHOOSE_FLEE = {1, 1};
    };
}