#include "renderer/SceneManager.hpp"
#include "imgui-SFML.h"

using namespace std;
using namespace sf;

namespace renderer
{
    SceneManager::SceneManager(const string& configFile)
    {
        std::ifstream config(configFile);
        Json json = Json::object();

        if(config)
        {
            config >> json;
        }
        else
        {
            cerr << "Warning: could not find config file " << configFile;
            cerr << "." << endl << "Window configs are set to default." << endl;
        }

        const auto width = json.value("width", 800);
        const auto height = json.value("height", 800);
        const auto title = json.value("title", "Pokemon");
        const auto fullscreen = json.value("fullscreen", false);

        auto styles = Style::Default;
        if(fullscreen)
        {
            styles = Style::Fullscreen;
        }

        m_window.create(VideoMode(width, height), title.c_str(), styles);

        assert(m_font.loadFromFile(assets::getFilePath("ProggyClean.ttf")));
        ImGui::SFML::Init(m_window);
    }

    void renderer::SceneManager::pushScene(Scene *scene)
    {
        m_scenes.emplace_back(scene);
    }

    sf::RenderWindow &SceneManager::window()
    {
        return m_window;
    }

    const sf::RenderWindow &SceneManager::window() const
    {
        return m_window;
    }

    void SceneManager::renderAll()
    {
        m_window.clear();

        // Get last opaque scene
        auto start = find_if(begin(m_scenes), end(m_scenes), [](const auto &scene) {
            return scene->isOpaque();
        });

        // If there is no opaque scene, should render all the scenes
        if (start == end(m_scenes))
        {
            start = begin(m_scenes);
        }

        // Render the scenes
        for_each(start, end(m_scenes), [](const auto &scene) {
            scene->renderScene();
        });

        notify(OnRender{
            .source = *this
        });

        m_window.display();

        ImGui::SFML::Render(m_window);
    }

    vec2f SceneManager::size() const
    {
        return vec2f(m_window.getSize());
    }

    const sf::Font &SceneManager::font() const
    {
        return m_font;
    }

    void SceneManager::show()
    {
        notify(OnGameOpen{
            .source = *this
        });

        while (m_window.isOpen())
        {
            if (m_controller)
            {
                m_controller->frameStarted();
            }

            handleEvents();
            updateAll();
            renderAll();
        }

        notify(OnGameClose{
            .source = *this
        });
    }

    void SceneManager::handleEvents()
    {
        sf::Event e{};
        while (m_window.pollEvent(e))
        {
            ImGui::SFML::ProcessEvent(e);

            notify(OnInputEvent{
                .source = *this,
                .e = e
            });

            switch (e.type)
            {
                case sf::Event::Closed:
                    m_window.close();
                    break;

                default:
                    if (m_controller)
                    {
                        Command command;
                        if (m_controller->handleEvent(e, command))
                        {
                            for (auto it = m_scenes.rbegin(); it != m_scenes.rend(); ++it)
                            {
                                auto &scene = *it;
                                if (scene->handleCommand(command))
                                {
                                    m_controller->markAsConsumed(command);
                                    break;
                                }
                            }
                        }
                    }
                    break;
            }
        }
    }

    Controller &SceneManager::controller()
    {
        assert(m_controller);
        return *m_controller;
    }

    const Controller &SceneManager::controller() const
    {
        assert(m_controller);
        return *m_controller;
    }

    void SceneManager::setController(Controller *controller)
    {
        m_controller.reset(controller);
    }

    void SceneManager::updateAll()
    {
        // Notify frame update
        notify(OnUpdate{
            .source = *this,
            .delta = m_delta.restart()
        });

        // Remove all closed scenes first
        m_scenes.erase(
            remove_if(
                m_scenes.begin(),
                m_scenes.end(),
                [](const auto& scene) { return scene->isClosed(); }
            ),
            m_scenes.end()
        );

        // Update all scenes
        for (auto &scene : m_scenes)
        {
            scene->update();
        }
    }
}