#pragma once

#include <SFML/Graphics.hpp>
#include "Region.hpp"
#include "tilemap/TilemapEngine.hpp"
#include "config/Math.hpp"

namespace renderer
{
    /// Window pixel unit. It's just float, but it's useful for self-documenting.
    using WinPx = float;

    class SFMLRenderer : public Region
    {
    public:
        SFMLRenderer(int winHeight, int winWidth);
        ~SFMLRenderer() override = default;

        void render(const Tm::Region &region) override;

        void waitCloseByUser();

        sf::Vector2<WinPx> windowSize() const { return sf::Vector2<WinPx>(m_window.getSize()); }

        void gameLoop(Tm::Region &region, Tm::TilemapEngine &controller);

    private:
        void renderLayer(const Tm::StaticLayer &layer, const sf::Vector2<WinPx> &renderingOffset,
                         const sf::Vector2<WinPx> &tileSize);

        void renderPlayer(const sf::Vector2<WinPx> &renderingOffset, const sf::Vector2<WinPx> &tileSize);


        Tm::TilemapEngine *m_engine;
        sf::RenderWindow m_window;
        sf::Font m_font;
        sf::Texture m_tileset;
    };

}

