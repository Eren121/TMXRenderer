#include "renderer/Scene.hpp"
#include "renderer/SceneManager.hpp"

namespace renderer
{
    Scene::Scene(SceneManager &sceneManager)
        : m_sceneManager(sceneManager)
    {
        const auto &sceneSize = sceneManager.size();

        // Normalize coords
        // so (1, 1) equals to full windows size
        m_coordSystem.scale(sceneSize);
    }

    sf::RenderWindow &Scene::window()
    {
        return m_sceneManager.window();
    }

    void Scene::close()
    {
        notify(OnSceneClose{this });
        m_isClosed = true;
    }

    vec2f Scene::size() const
    {
        return m_sceneManager.size();
    }

    bool Scene::isGame() const
    {
        return false;
    }

    bool Scene::isOpaque() const
    {
        return false;
    }
}