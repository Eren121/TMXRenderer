#pragma once

#include "renderer/SceneManager.hpp"

namespace Tm
{
    class Engine;

    class System
    {
    public:
        System(renderer::SceneManager &sceneManager, Engine &engine);
        virtual ~System() = default;

        virtual void update() = 0;

        /**
         * @return true if there is no ui open and realtime input can be used.
         */
        bool hasFocus() const;

    protected:
        renderer::SceneManager &m_sceneManager;
        Engine &m_engine;
    };
}