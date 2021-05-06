#pragma once

#include "State.hpp"
#include "renderer/Scene.hpp"
#include "renderer/SceneManager.hpp"
#include "ui/MenuWidget.hpp"

namespace Btl
{
    class BattleScene
        : public renderer::Scene
    {
    public:
        BattleScene(renderer::SceneManager &parent, entt::registry &registry, entt::entity opponent);

        bool isOpaque() const override;
        void renderScene() override;
        void update() override;
        bool handleCommand(Command command) override;

    protected:
        void renderHealthBars();


    private:
        entt::registry &m_registry;
        entt::entity m_opponent;
        entt::entity m_player;

        /// Current state (state pattern)
        std::unique_ptr<State> m_state;
    };
}