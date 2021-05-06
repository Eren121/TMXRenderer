#pragma once

#include "State.hpp"

namespace Btl
{
    /// State for the battle when the battle begins
    class InitState : public State
    {
    public:
        using State::State;

        std::unique_ptr<State> update() override;
    };
}

