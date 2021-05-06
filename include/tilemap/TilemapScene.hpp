#pragma once

#include "renderer/Scene.hpp"
#include "tilemap/Engine.hpp"
#include "tilemap/Tileset.hpp"
#include "tilemap/TileRenderer.hpp"
#include "tilemap/systems/InteractionSystem.hpp"
#include "tilemap/RegionLoader.hpp"
#include <SFML/Graphics.hpp>

namespace Tm
{
    class TilemapScene : public renderer::Scene
    {
    public:
        TilemapScene(renderer::SceneManager& parent);
        ~TilemapScene() override = default;

        void update() override;
        void renderScene() override;

        bool isGame() const override;

    protected:
        void showImguiDebugWindow() override;

    private:
        bool handleCommand(Command command) override;

        RegionLoader m_regionLoader;
        Engine m_engine;

        /// Load on the fly the needed textures from sprites
        std::map<std::string, sf::Texture> m_texturesResource;

        /// Cache for each frame
        vec2f m_cameraPos;

        TileRenderer m_tileRenderer;
    };
}