#include "config/Config.hpp"
#include "renderer/ImGui.hpp"
#include <fstream>
#include <SFML/Window.hpp>

using namespace sf;

Config::Config(const string &configFile)
{
    std::ifstream config(configFile);
    Json json = Json::object();

    if (config)
    {
        config >> json;
    }
    else
    {
        cerr << "Warning: could not find config file " << configFile;
        cerr << "." << endl << "Window configs are set to default." << endl;
    }

    m_windowSize.x = json.value("width", 800);
    m_windowSize.y = json.value("height", 800);
    m_title = json.value("title", "Pokemon");
    m_fullscreen = json.value("fullscreen", false);
    m_isDebugMode = json.value("debugMode", false);
    m_mapFileName = json.at("map");
    m_fontFileName = json.value("font", "ProggyClean.ttf");
    m_tileSizeInPx = json.value("tileSizeInPx", 128);
    m_noImguiIni = json.value("noImguiIni", true);
}

VideoMode Config::videoMode() const
{
    return VideoMode(m_windowSize.x, m_windowSize.y);
}

sf::Uint32 Config::windowStyle() const
{
    auto styles = Style::Default;

    if (m_fullscreen)
    {
        styles = Style::Fullscreen;
    }

    return styles;
}

void Config::showImguiDebugWindow()
{
    if(ImGui::TreeNode("View"))
    {
        if (ImGui::Checkbox("fullscreen", &m_fullscreen))
        {
            notifyChange(ConfigParameter::FULLSCREEN);
        }

        if (ImGui::SliderInt("Tile size px", &m_tileSizeInPx, 0, 1024))
        {
            notifyChange(ConfigParameter::TILE_SIZE_PX);
        }

        // Exact AND slider
        ImGui::InputInt("Tile size px exact", &m_tileSizeInPx);
        ImGui::TreePop();
    }
}

void Config::notifyChange(ConfigParameter parameter)
{
    notify(OnConfigParameterChanged{
        .source = *this,
        .parameter = parameter
    });
}
