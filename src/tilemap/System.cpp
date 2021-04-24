#include "tilemap/System.hpp"
#include "tilemap/Engine.hpp"

namespace Tm
{
    System::System(renderer::SceneManager &sceneManager, Tm::Engine &engine)
        : m_sceneManager(sceneManager),
          m_engine(engine)
    {
    }

    bool System::hasFocus() const
    {
        return m_sceneManager.topScene().isGame();
    }
}