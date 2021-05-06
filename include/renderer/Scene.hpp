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
        explicit Scene(SceneManager &parent);
        ~Scene() override = default;

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

        /// @brief When debugging is enabled, relevant options can be drawn here
        /// @remarks Centralize rendering to have only one Imgui window instead of several small ones
        /// @remarks ImGui::BeginChild() for integration into Debug Window instead of ImGui::Begin()
        virtual void showImguiDebugWindow() { }

        /// Get the size of the scene, that is the size of the window.
        vec2f size() const;

        /// An opaque scene means the lower scenes on the stacks should not be rendered.
        /// False by default.
        virtual bool isOpaque() const;

        auto isClosed() const { return m_isClosed; }

        auto& parent() const { return m_parent; }
        auto& parent() { return m_parent; }

        auto& coordSystem() const { return m_coordSystem; }

        /// Close the scene.
        /// It only works if it's the top scene.
        /// close() call "delete this", so do not use any member variable after calling close().
        void close();

    protected:

        SceneManager &m_parent;

        /// Transformation that normalize the rendering window coordinates into [0; 1].
        /// Can be modified by inheriting scenes, it's really just an utility.
        sf::Transform m_coordSystem;


        // Normalize the size of a sprite
        // Because it's size is equal to the texture size by default
        static inline void normalize(sf::Sprite &sprite) {
            sprite.setScale(1.0f / sf::size(sprite.getTextureRect()));
        }

    private:

        /// Set to true to close the scene
        bool m_isClosed = false;
    };
}

