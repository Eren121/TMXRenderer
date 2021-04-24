#pragma once

#include "Scene.hpp"
#include "controller/Controller.hpp"
#include "common.hpp"
#include <SFML/Graphics.hpp>
#include <stack>

namespace renderer
{
    /// Event called when the SceneManager enter the game loop.
    /// That is the window just open.
    struct OnGameOpen
    {
        SceneManager &source;
    };

    /// Event called when the process stop
    /// That is the window is closing.
    struct OnGameClose
    {
        SceneManager &source;
    };

    /// Event called when the SceneManager is in event processing phase and an input event occured.
    /// The event is always sent whatever it is, and do not affects how this event is treated (can't be cancelled).
    struct OnInputEvent
    {
        SceneManager &source;
        sf::Event &e;
    };

    /// Event called when the SceneManager is in updating phase.
    /// Put logic here.
    struct OnUpdate
    {
        SceneManager &source;

        /// Time difference between previous frame and current frame.
        sf::Time delta;
    };

    /// Event called when the SceneManager is in rendering phase.
    struct OnRender
    {
        SceneManager &source;
    };

    /**
     * @brief Render all loaded scenes like a stack. The bottom scene should be the game world itself, but a scene
     *        can also be a ui.
     */
    class SceneManager final
        : public obs::Subject<OnInputEvent, OnUpdate, OnRender, OnGameOpen, OnGameClose>
    {
    public:
        SceneManager(const string &configFile);

        /// Add a scene over all others scenes.
        /// This new added scene has priority for all inputs and is rendered last.
        /// Rendered last means in fact top-view, because the scene cannot be overwrited by the others scenes.
        void pushScene(Scene *scene);

        const Scene &topScene() const { return *m_scenes.back(); }

        auto &scenes() { return m_scenes; }

        sf::RenderWindow &window();
        const sf::RenderWindow &window() const;

        const sf::Font &font() const;

        /// Get the size of the window. Convenient because returns vec2f instead of vec2i
        vec2f size() const;

        /// Game loop
        void show();

        /// The default size of the font
        unsigned int charSize() const { return 60; }

        Controller &controller();
        const Controller &controller() const;
        void setController(Controller *controller);

    private:
        void handleEvents();
        void updateAll();
        void renderAll();

        /// Scene stack.
        /// The top-scene is the last one inserted (end of array).
        std::vector<std::unique_ptr<Scene>> m_scenes;

        sf::RenderWindow m_window;

        UniquePtr<Controller> m_controller;

        /// Default font
        sf::Font m_font;

        /// Clock reseted at each call to update(), that is once per frame
        /// Measure time between previous frame and current frame
        sf::Clock m_delta;
    };
}


