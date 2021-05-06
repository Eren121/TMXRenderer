#include "battle/InitState.hpp"
#include "battle/PrepareTurnState.hpp"

namespace Btl
{
    std::unique_ptr<State> InitState::update()
    {
        return std::make_unique<PrepareTurnState>(m_scene);
    }
}
