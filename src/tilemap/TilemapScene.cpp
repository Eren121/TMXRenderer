#include "tilemap/TilemapScene.hpp"
#include "renderer/SceneManager.hpp"
#include "renderer/ImGui.hpp"
#include "config/Debug.hpp"
#include <fmt/core.h>
#include <fmt/ostream.h>

using namespace sf;
using namespace std;

using fmt::format;

static bool tileInfoEnabled{false};

namespace Tm
{
    TilemapScene::TilemapScene(renderer::SceneManager &parent)
        : Scene(parent),
          m_regionLoader(assets::getFilePath(parent.config().mapFileName())),
          m_engine(parent, m_regionLoader.region()),
          m_tileRenderer(m_regionLoader.tileset())
    {
    }

    void TilemapScene::update()
    {
        m_engine.update();
    }

    void TilemapScene::renderScene()
    {
        const auto &region = m_engine.region();

        // Example:
        //  sight=3
        //  there should be 7 tiles rendered in the window vertically and horizontally.
        //  if window is 700px, each tile size is 100px.
        //  so tileSize=windowSize/viewportSize

        if (!region.hasPlayer())
        {
            return;
        }

        const auto playerID = region.player();
        const auto playerPos = m_engine.cameraPosition(region);
        m_cameraPos = m_engine.cameraPosition(region);

        const vec2f tileSizeInPx(m_parent.config().tileSizeInPx());
        const auto cameraSize = vec2f(m_parent.size()) / tileSizeInPx;
        const auto cameraOrigin(m_cameraPos - cameraSize / 2.0f);

        for (const auto &layer : region.layers())
        {
            // The tiles are rendered in world coordinates (1 tile = 1 unit)
            // Pass a transform to transform the world coordinate into view coordinates
            // that is what the player see: the player's camera

            sf::Transform view;

            // Move into camera coordinates
            view = sf::Transform().translate(-cameraOrigin) * view;

            // Move into window coordinates
            view = sf::Transform().scale(tileSizeInPx) * view;

            const vec2i begin(floor(m_cameraPos - cameraSize / 2.0f));
            const vec2i end(ceil(m_cameraPos + cameraSize / 2.0f));
            const sf::IntRect bounds{begin, end - begin};

            layer->render(window(), m_tileRenderer, bounds, view);
        }
    }

    bool TilemapScene::handleCommand(Command)
    {
        return false;
    }

    bool TilemapScene::isGame() const
    {
        return true;
    }

    void TilemapScene::showImguiDebugWindow()
    {
        const auto &region = m_engine.region();

        if(ImGui::TreeNode("Tilemap debugging"))
        {
            const auto &playerID = m_engine.region().player();
            auto &playerPos = m_engine.region().registry().get<Tm::Position>(playerID);
            ImGui::InputInt2("Player position", reinterpret_cast<int *>(&playerPos));

            ImGui::Checkbox("No collisions", &debugState.noCollisions);

            ImGui::Checkbox("Tile info", &tileInfoEnabled);

            if(ImGui::TreeNode("Tile inspector"))
            {
                static vec2i s_pos;
                ImGui::InputInt2("Position to inspect", reinterpret_cast<int *>(&s_pos));

                static bool posLinked = false;
                ImGui::Checkbox("Link to the player position", &posLinked);

                if (posLinked)
                {
                    s_pos = playerPos;
                }

                for (int i = 0; i < int(region.layers().size()); ++i)
                {
                    const auto &layerBase = region.layers().at(i);
                    const auto &walkable = layerBase->canMoveTo(s_pos);
                    const auto &name = layerBase->name();
                    int gid = 0;

                    // Draw tile only for tile layers
                    if (layerBase->type() == tmx::Layer::Type::Tile)
                    {
                        const auto &layer = dynamic_cast<Tm::LayerOfTiles &>(*layerBase);
                        gid = layer.getGID(s_pos);
                    }

                    const auto &label = format("layer '{}', gid={} walkable={}\n", name, gid, walkable);
                    ImGui::Selectable(label.c_str(), false);
                }

                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
    }
}