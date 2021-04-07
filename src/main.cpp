#include <iostream>
#include "tilemap/Region.hpp"
#include "renderer/SFMLRenderer.hpp"
#include "controller/KeyboardController.hpp"
#include "config/Json.hpp"
#include "tilemap/RegionLoader.hpp"

int main()
{
    const int tileSize(80);
    const sf::Vector2i sight(8, 4);
    const sf::Vector2i viewport(sf::Vector2f(sight) * 2.0f + 1.0f);
    const sf::Vector2i win(viewport * tileSize);

    Tm::RegionLoader loader("map.json");
    auto &region = loader.region();

    renderer::SFMLRenderer renderer(win.y, win.x);
    KeyboardController controller;
    Tm::TilemapEngine engine(controller);

    renderer.gameLoop(region, engine);
    return 0;
}
