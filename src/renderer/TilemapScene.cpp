#include "renderer/TilemapScene.hpp"
#include "renderer/SceneManager.hpp"
#include "renderer/ImGui.hpp"
#include "config/Debug.hpp"
#include <fmt/core.h>
#include <fmt/ostream.h>

using namespace sf;
using namespace std;

using fmt::format;

static bool tileInfoEnabled{false};

namespace renderer
{
    TilemapScene::TilemapScene(SceneManager &parent)
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

            //renderLayer(layer, playerPos, tileSize);
        }
        /*
        auto view = region.registry().view<const Tm::Character, const Tm::Position>();

        for (auto entity : view)
        {
            renderEntity(entity, tileSizeInPx);
        }
*/
    }

    void TilemapScene::renderLayer(const Tm::LayerOfTiles &layer, const vec2f &cameraCenter,
                                   const vec2f &tileSize)
    {
        // The count of tiles that fit in the window (can be float if the window is not exact multiple of tileSize)
        const auto cameraSize = vec2f(m_parent.size()) / tileSize;
        const vec2i begin(max(vec2i(cameraCenter
                                    - cameraSize / 2.0f), vec2i{0, 0}));
        const vec2i end(min(vec2i(ceil(cameraCenter
                                       + cameraSize / 2.0f)), layer.size()));


        const auto cameraOrigin(cameraCenter - cameraSize / 2.0f);

        for (int y = begin.y; y < end.y; ++y)
        {
            for (int x = begin.x; x < end.x; ++x)
            {
                const vec2f pos(x, y);
                const auto type = layer[{x, y}];

                if (type)
                {

                    const auto &textureFile = type->tmx().imagePath;
                    const auto &imagePosition(type->tmx().imagePosition);
                    const auto &imageSize(type->tmx().imageSize);

                    if (!m_texturesResource.contains(textureFile))
                    {
                        /// Texture not already loaded, load it
                        auto &texture = m_texturesResource[textureFile];

                        /// Assert the texture is found
                        /// If the texture is not found, exit with error
                        assert(texture.loadFromFile(assets::getFilePath(textureFile)));
                    }

                    /// Now texture should always been already/just preloaded, just get a pointer to it
                    const auto &texture = m_texturesResource.at(textureFile);

                    // Sprite sub-rect in pixel in local texture file
                    Sprite sprite(texture, IntRect(
                        imagePosition.x, imagePosition.y,
                        imageSize.x, imageSize.y));

                    sf::Transform model;

                    // Make the tile size (1, 1)
                    model.scale(1.0f / sf::size(sprite.getTextureRect()));

                    // Move into the tile coordinates
                    model = sf::Transform().translate(pos) * model;

                    // Move into camera coordinates
                    model = sf::Transform().translate(-cameraOrigin) * model;

                    // Move into window coordinates
                    model = sf::Transform().scale(tileSize) * model;


                    const sf::Transform mvp = model;

                    window().draw(sprite, mvp);

                    if (tileInfoEnabled)
                    {
                        const int gid = type->gid();
                        const int lid = type->lid();
                        Text text(
                            format("{}\nLID={}\nGID={}\nwalk={}", pos, lid, gid, type->walkable()),
                            m_parent.font(), tileSize.x);

                        text.setFillColor(Color::White);

                        text.setPosition(mvp.transformPoint(0.0f, 0.0f));
                        text.setScale(tileSize / sf::size(text.getLocalBounds()) * 0.8f);
                        text.setScale(text.getScale().x, text.getScale().x);

                        window().draw(text);
                    }
                }
            }
        }
    }

    void TilemapScene::renderEntity(entt::entity entity, const vec2f &tileSize)
    {
        auto &region = m_engine.region();
        auto &registry = region.registry();
        const auto &pos = m_engine.movementSystem().getInterpolatedPosition(entity);
        const auto &sprite_comp = registry.try_get<Tm::Sprite>(entity);
        const auto &character = registry.try_get<Tm::Character>(entity);
        const auto &moving = registry.try_get<Tm::IsMoving>(entity);

        const auto cameraSize = vec2f(m_parent.size()) / tileSize;
        const auto cameraOrigin(m_cameraPos - cameraSize / 2.0f);

        // Default direction when the entity is non-orientable
        Direction direction = Direction::DOWN;

        if (!sprite_comp)
        {
            // Sprite is not renderable
            return;
        }

        if (character)
        {
            // The entity is a character
            // It also has a facing direction and can be rendered accordingly
            direction = character->facingDirection;
        }

        // Get the GID of the sprite when it's moving or not and relative to it's direction
        Tm::GID gid = sprite_comp->gid(direction, moving != nullptr);

        if (gid == 0)
        {
            // Zero is null tile
            return;
        }

        // Animate the sprite if this tile is animated by Tiled Animator Editor
        if (!m_regionLoader.tileset()[gid].tmx().animation.frames.empty())
        {
            /// TODO check if animation gid is same as sprite gid

            auto &anim = registry.get_or_emplace<Tm::SpriteIsAnimating>(entity, Tm::SpriteIsAnimating{
                .frame = 0,
                .start = sf::getCurrentTime()
            });
            const auto &frames = m_regionLoader.tileset()[gid].tmx().animation.frames;
            const tmx::Tileset::Tile::Animation::Frame *frame = &frames.at(anim.frame);

            Time frameDuration = milliseconds(frame->duration);
            const Time currentTime = getCurrentTime();


            // Search next frame if needed
            // Unlikely, under some circonstances (like lag, high rate animation), skip multiples frames
            // But likely +1 frame or +0 (same frame)
            while (currentTime > anim.start + frameDuration)
            {
                // Add time (step by step)
                anim.start += frameDuration;

                // Increment frame
                anim.frame++;
                if (anim.frame >= int(frames.size()))
                {
                    anim.frame = 0;
                }

                // Get updated frameDuration
                frame = &frames.at(anim.frame);
                frameDuration = milliseconds(frame->duration);
            }

            // Tiled save tile ID of animations relative to the tileset (LID)
            // But tmx convert it to GID, so we already have it.
            // This does not means we can use tiles from different tilesets for one animation;
            // it's actually not possible inside Tiled Editor (but actually possible in the engine)
            gid = frames.at(int(anim.frame)).tileID;

            if (gid == 0)
            {
                // Zero is null tile
                cerr << "warning: null tile in animation" << endl;
                return;
            }
        }

        const auto &type = m_regionLoader.tileset()[gid];
        const auto &textureFile = type.tmx().imagePath;
        const auto &imagePosition = type.tmx().imagePosition;
        const auto &imageSize = type.tmx().imageSize;

        if (!m_texturesResource.contains(textureFile))
        {
            /// Texture not already loaded, load it
            auto &texture = m_texturesResource[textureFile];

            /// Assert the texture is found
            /// If the texture is not found, exit with error
            assert(texture.loadFromFile(assets::getFilePath(textureFile)));
        }

        /// Now texture should always been already/just preloaded, just get a pointer to it
        const auto &texture = m_texturesResource.at(textureFile);

        Sprite sprite(texture, IntRect(imagePosition.x, imagePosition.y, imageSize.x, imageSize.y));

        Transform model;

        // Make the tile size (1, 1)
        model.scale(1.0f / sf::size(sprite.getTextureRect()));

        // Rotate to the facing direction
        // Now done automatically be loading the right tile texture direction
        /*sf::Transform rotation;
        rotation.rotate(getAngle(direction), 0.5f, 0.5f);
        model = rotation * model;*/

        // Move into the tile coordinates
        model = Transform().translate(pos) * model;

        // Move into camera coordinates
        model = Transform().translate(-cameraOrigin) * model;

        // Move into window coordinates
        model = Transform().scale(tileSize) * model;


        window().draw(sprite, model);
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