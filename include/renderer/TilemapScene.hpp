#pragma once

#include "Scene.hpp"
#include "tilemap/Engine.hpp"
#include "tilemap/Tileset.hpp"
#include "tilemap/TileRenderer.hpp"
#include "tilemap/systems/InteractionSystem.hpp"
#include "tilemap/RegionLoader.hpp"
#include <SFML/Graphics.hpp>

namespace renderer
{
    class TilemapScene : public Scene
    {
    public:
        TilemapScene(SceneManager &parent);
        ~TilemapScene() override = default;

        void update() override;
        void renderScene() override;

        bool isGame() const override;

    protected:
        void renderLayer(const Tm::LayerOfTiles &layer, const vec2f &cameraCenter, const vec2f &tileSize);
        void renderEntity(entt::entity entity, const vec2f &tileSize);

        void showImguiDebugWindow() override;

    private:
        bool handleCommand(Command command) override;

        Tm::RegionLoader m_regionLoader;
        Tm::Engine m_engine;

        /// Load on the fly the needed textures from sprites
        std::map<std::string, sf::Texture> m_texturesResource;

        /// Cache for each frame
        vec2f m_cameraPos;

        Tm::TileRenderer m_tileRenderer;
    };
}