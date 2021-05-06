#pragma once

#include "State.hpp"
#include "ui/MenuWidget.hpp"
#include "observer/Observer.hpp"

namespace Btl
{
    /// The player choose the next action to do
    class PrepareTurnState : public State,
                             public obs::Observer<ui::OnOptionAccept>
    {
    public:
        PrepareTurnState(BattleScene &scene);

        void render() override;
        std::unique_ptr<State> update() override;
        bool handleCommand(Command command) override;

        void receiveEvent(const ui::OnOptionAccept &eventData) override;

    private:
        /// Menu for turn action
        ui::MenuWidget m_turnMenu;

        static inline const vec2i BTN_CHOOSE_MOVE {0, 0};
        static inline const vec2i BTN_CHOOSE_PKM {0, 1};
        static inline const vec2i BTN_CHOOSE_OBJ {1, 0};
        static inline const vec2i BTN_CHOOSE_FLEE {1, 1};
    };
}