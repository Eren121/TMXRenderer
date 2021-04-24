#include <iostream>
#include "tilemap/Region.hpp"
#include "controller/KeyboardController.hpp"
#include "config/Json.hpp"
#include "tilemap/RegionLoader.hpp"
#include "renderer/SceneManager.hpp"
#include "renderer/TilemapScene.hpp"
#include "renderer/ImGuiObserver.hpp"
#include "battle/RandomAI.hpp"

struct NC
{
    int a;
};

NC& x()
{
    static NC nc;
    return nc;
}

void test()
{
    entt::registry r;
    const auto& cr = r;
    auto e = r.create();
    r.emplace<NC>(e);

    auto comp = cr.get<NC>(e);
    comp.a = 0;
}

int main()
{
    renderer::SceneManager sceneManager(assets::getFilePath("config.json"));
    renderer::ImGuiObserver imgui(sceneManager);
    sceneManager.setController(new KeyboardController());

    sceneManager.pushScene(new renderer::TilemapScene(sceneManager));
    sceneManager.show();

    return 0;
}
