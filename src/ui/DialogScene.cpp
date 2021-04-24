#include "ui/DialogScene.hpp"

namespace ui
{
    DialogScene::DialogScene(renderer::SceneManager &manager, const string &text)
        : Scene(manager),
          m_text(text, manager.font(), 140)
    {
        const auto bounds = m_text.getLocalBounds();

        m_text.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
        m_text.setPosition({size().x / 2.0f, size().y - 150.0f});
    }

    void DialogScene::update()
    {
    }

    void DialogScene::renderScene()
    {
        window().draw(m_text);
    }

    bool DialogScene::handleCommand(Command command)
    {
        if (command == Command::B || command == Command::A)
        {
            close();
        }

        return true;
    }
}