#pragma once

#include "controller/Command.hpp"
#include <memory>

namespace Btl
{
    class BattleScene;

    /// State of the battle
    /// Instanciable, by default does nothing
    class State
    {
    public:
        State(BattleScene& scene);
        virtual ~State() = default;

        /// Handle state logic
        /// Can modify the current state for the next frame
        /// @returns nullptr if the state do not need to be modified (do not return *this)
        ///          or the new state
        virtual std::unique_ptr<State> update() = 0;

        /// Render the current state scene
        virtual void render() {}

        virtual bool handleCommand(Command command) { return false; }

    protected:
        BattleScene& m_scene;
    };
}