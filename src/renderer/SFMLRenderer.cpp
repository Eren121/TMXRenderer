#include "renderer/SFMLRenderer.hpp"
#include "config/Assets.hpp"
#include "config/Math.hpp"

using namespace std;
using namespace sf;
using std::to_string;

namespace renderer
{
    SFMLRenderer::SFMLRenderer(int winHeight, int winWidth)
        : m_window(sf::VideoMode(winWidth, winHeight), "Title"),
          m_engine(nullptr)
    {
        assert(m_font.loadFromFile(assets::getFileName("ProggyClean.ttf")));
        assert(m_tileset.loadFromFile(assets::getFileName("tiles.png")));
    }

    void SFMLRenderer::render(const Tm::Region &region)
    {
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
        const auto playerPos = m_engine->getPlayerMovingPosition(region);

        const sf::Vector2<WinPx> viewportSize(sf::Vector2<WinPx>(player.viewportSize()));
        sf::Vector2<WinPx> tileSize(windowSize() / viewportSize);
        tileSize = sf::Vector2<WinPx>{1, 1} * 16.0f;

        // Rendering offset because of the player position
        // Example:
        //  If window size is (3, 3) tiles
        //  To render without offset the player should be in position (1, 1)
        const sf::Vector2<WinPx> renderingOffset =
            -(sf::Vector2<WinPx>(playerPos) + 0.5f)
            +windowSize() /  / 2.0f;

        for (auto &layer: region.layers())
        {
            renderLayer(layer, renderingOffset, tileSize);
        }

        renderPlayer(renderingOffset, tileSize);
    }

    void SFMLRenderer::renderLayer(const Tm::StaticLayer &layer, const Vector2<WinPx> &renderingOffset,
                                   const sf::Vector2<WinPx> &tileSize)
    {
        for (int y = 0; y < layer.height(); ++y)
        {
            for (int x = 0; x < layer.width(); ++x)
            {
                const auto type = layer[{x, y}];

                if (type)
                {
                    Sprite sprite(m_tileset,
                                  IntRect(16 + type->atlasPos().x * 16, 16 + type->atlasPos().y * 16, 16, 16));
                    const Vector2f tilePos(x, y);
                    const auto position((renderingOffset + tilePos) * tileSize);

                    sprite.setScale(tileSize / 16.0f);
                    sprite.setPosition(position);
                    m_window.draw(sprite);

                    sf::Text text(
                        to_string(sf::Vector2i(x, y)) + "\n" + type->name() + "\n" + to_string(type->walkable()),
                        m_font, 18);
                    text.setPosition(position);
//                    m_window.draw(text);
                }
            }
        }
    }

    void SFMLRenderer::renderPlayer(const Vector2<WinPx> &renderingOffset, const Vector2<WinPx> &tileSize)
    {
        int gid = 266;
        int gidx = gid % 24;
        int gidy = gid / 24;

        Sprite sprite(m_tileset, IntRect(16 + gidx * 16, 16 + gidy * 16, 16, 16));
        const auto position((sf::Vector2f(m_window.getSize()) - tileSize) / 2.0f);

        sprite.setScale(tileSize / 16.0f);
        sprite.setPosition(position);
        m_window.draw(sprite);
    }

    void SFMLRenderer::waitCloseByUser()
    {
        while (m_window.isOpen())
        {
            sf::Event e{};
            while (m_window.pollEvent(e))
            {
                switch (e.type)
                {
                    case sf::Event::Closed:
                        m_window.close();
                        break;

                    default:
                        break;
                }
            }
        }
    }

    void SFMLRenderer::gameLoop(Tm::Region &region, Tm::TilemapEngine &engine)
    {
        m_engine = &engine;

        while (m_window.isOpen())
        {
            sf::Event e{};
            while (m_window.pollEvent(e))
            {
                switch (e.type)
                {
                    case sf::Event::Closed:
                        m_window.close();
                        break;

                    default:
                        break;
                }
            }

            engine.update(region);

            m_window.clear();
            render(region);
            m_window.display();
        }
    }
}