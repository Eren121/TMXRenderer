#include "renderer/TilemapScene.hpp"
#include "renderer/SceneManager.hpp"
#include "renderer/ImGui.hpp"

using namespace sf;
using namespace std;

namespace renderer
{
    TilemapScene::TilemapScene(SceneManager &sceneManager)
        : Scene(sceneManager),
          m_engine(sceneManager)
    {
        assert(m_tileset.loadFromFile(assets::getFilePath("tiles.png")));
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
        const auto &player = region.registry().get<Tm::Player>(playerID);
        const auto playerPos = m_engine.cameraPosition(region);
        m_cameraPos = m_engine.cameraPosition(region);

        const vec2f viewportSize(vec2f(player.viewportSize()));
        vec2f tileSize(m_sceneManager.size() / viewportSize);
        tileSize = vec2f{1, 1} * 128.0f;

        // Rendering offset because of the player position
        // Example:
        //  If window size is (3, 3) tiles
        //  To render without offset the player should be in position (1, 1)
        const vec2f renderingOffset =
            -(vec2f(playerPos) + 0.5f)
            + m_sceneManager.size() / 2.0f;

        for (auto &layer : region.layers())
        {
            renderLayer(layer, playerPos, tileSize);
        }

        auto view = region.registry().view<const Tm::Character, const Tm::Position>();

        for (auto &&[entity, character, position]: view.each())
        {
            const auto pos = m_engine.movementSystem().getInterpolatedPosition(region, entity);
            renderPlayer(pos, character.facingDirection, tileSize);
        }

        ImGui::Begin("Debug");
        {
            ostringstream ss;
            ss << "Position: ";
            ss << vec2i(playerPos);

            auto pos = ss.str();
            ImGui::Text(pos.c_str());
        }
        ImGui::End();
    }

    void TilemapScene::renderLayer(const Tm::StaticLayer &layer, const vec2f &cameraPos,
                                   const vec2f &tileSize)
    {
        // The count of tiles that fit in the window (can be float if the window is not exact multiple of tileSize)
        const auto windowTileSize = vec2f(m_sceneManager.size()) / tileSize;
        const vec2i begin(max(vec2i(cameraPos
                                    - windowTileSize / 2.0f), vec2i{0, 0}));
        const vec2i end(min(vec2i(ceil(cameraPos
                                       + windowTileSize / 2.0f)), layer.size()));

        for (int y = begin.y; y < end.y; ++y)
        {
            for (int x = begin.x; x < end.x; ++x)
            {
                const auto type = layer[{x, y}];

                if (type)
                {
                    Sprite sprite(m_tileset,
                                  IntRect(16 + type->atlasPos().x * 16, 16 + type->atlasPos().y * 16, 16, 16));
                    const Vector2f tilePos(x, y);

                    // Position in the world (unit: tile)
                    auto position(tilePos);

                    // Transform position from world to camera (unit: tile)
                    // Here parallax effect is done
                    position = (position - cameraPos);

                    // Transform position from camera to window (unit: pixel)
                    position = position * tileSize;
                    position += vec2f(m_sceneManager.size()) / 2.0f;

                    sprite.setScale(tileSize / 16.0f);
                    sprite.setScale(sprite.getScale());
                    sprite.setPosition(position);
                    window().draw(sprite);

                    sf::Text text(
                        to_string(sf::Vector2i(x, y)) + "\n" + type->name() + "\n" + to_string(type->walkable()),
                        m_sceneManager.font(), 18);
                    text.setPosition(position);
//                    m_window.draw(text);
                }
            }
        }
    }

    void TilemapScene::renderPlayer(const vec2f &playerPos, Direction direction, const vec2f &tileSize)
    {
        int gid = 266;
        int gidx = gid % 24;
        int gidy = gid / 24;

        Sprite sprite(m_tileset, IntRect(16 + gidx * 16, 16 + gidy * 16, 16, 16));

        // Position in the world (unit: tile)
        auto position(playerPos);

        // Transform position from world to camera (unit: tile)
        position = (position - m_cameraPos);

        // Transform position from camera to window (unit: pixel)
        position = position * tileSize;
        position += vec2f(m_sceneManager.size()) / 2.0f;

        sprite.setOrigin(vec2f(8, 8));
        position += tileSize / 2.0f;
        sprite.setScale(tileSize / 16.0f);

        // Render orientation
        switch (direction)
        {
            case Direction::UP:
                sprite.setRotation(180.0f);
                break;

            case Direction::DOWN:
                break;

            case Direction::LEFT:
                sprite.setRotation(90.0f);
                break;

            case Direction::RIGHT:
                sprite.setRotation(-90.0f);
                break;
        }

        sprite.setPosition(position);
        window().draw(sprite);
    }

    bool TilemapScene::handleCommand(Command command)
    {
        return false;
    }

    bool TilemapScene::isGame() const
    {
        return true;
    }
}