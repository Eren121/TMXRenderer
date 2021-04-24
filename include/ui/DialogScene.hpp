#pragma once

#include "renderer/Scene.hpp"
#include "renderer/SceneManager.hpp"

namespace ui
{
    /// Textbox that open when speaking to a NPC
    class DialogScene : public renderer::Scene
    {
    public:
        DialogScene(renderer::SceneManager &manager, const std::string &text);
        void update() override;
        void renderScene() override;
        bool handleCommand(Command command) override;

    private:
        sf::Text m_text;
    };
}