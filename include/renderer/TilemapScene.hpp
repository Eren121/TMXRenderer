#pragma once

#include "Scene.hpp"
#include "tilemap/Engine.hpp"
#include "tilemap/Tileset.hpp"
#include "tilemap/systems/InteractionSystem.hpp"
#include <SFML/Graphics.hpp>

namespace renderer
{
    class TilemapScene : public Scene
    {
    public:
        TilemapScene(SceneManager &sceneManager);
        ~TilemapScene() override = default;

        void update() override;
        void renderScene() override;

    protected:
        void renderLayer(const Tm::StaticLayer &layer, const vec2f &cameraPos, const vec2f &tileSize);
        void renderPlayer(const vec2f &playerPos, Direction direction, const vec2f &tileSize);

    private:
        bool handleCommand(Command command) override;
    public:
        bool isGame() const override;
    private:
        Tm::Engine m_engine;
        sf::Texture m_tileset;

        /// Cache for each frame
        vec2f m_cameraPos;
    };
}