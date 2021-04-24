#pragma once

#include "controller/Command.hpp"
#include "common.hpp"
#include <SFML/Graphics.hpp>

namespace renderer
{
    class SceneManager;

    class Scene;

    /// Event called when a scene is closed
    struct OnSceneClose
    {
        explicit OnSceneClose(Scene *scene) : source(scene) {}

        Scene *source;
    };

    /// A scene is anything that is drawn and self-contained: tileset world, battle, menus...
    class Scene : public obs::Subject<OnSceneClose>
    {

    public:
        Scene(SceneManager &sceneManager);
        virtual ~Scene() = default;

        /// Render the scene.
        /// Do not perform any logic here, just rendering.
        virtual void renderScene() = 0;

        /// Update the scene.
        /// Put the logic here.
        virtual void update() = 0;

        /// Wrapper of "m_sceneManager->window()".
        sf::RenderWindow &window();

        /// @return true if the command has been treated
        /// false if not, to pass the process to the next scene.
        virtual bool handleCommand(Command command) = 0;

        /// @return true if it's the game scene (2D tilemap world)
        virtual bool isGame() const;

        /// Get the size of the scene, that is the size of the window.
        vec2f size() const;

        /// An opaque scene means the lower scenes on the stacks should not be rendered.
        /// False by default.
        virtual bool isOpaque() const;

        auto isClosed() const { return m_isClosed; }

    protected:

        /// Close the scene.
        /// It only works if it's the top scene.
        /// close() call "delete this", so do not use any member variable after calling close().
        void close();

        SceneManager &m_sceneManager;

        /// Transformation that normalize the rendering window coordinates into [0; 1].
        /// Can be modified by inheriting scenes, it's really just an utility.
        sf::Transform m_coordSystem;

    private:

        /// Set to true to close the scene
        bool m_isClosed = false;
    };
}

