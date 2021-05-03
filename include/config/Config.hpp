#pragma once

#include "common.hpp"
#include <SFML/Window.hpp>

enum class ConfigParameter
{
    DEBUG_MODE,
    FULLSCREEN,
    TILE_SIZE_PX
};

class Config;

struct OnConfigParameterChanged
{
    Config &source;
    const ConfigParameter parameter;
};

class Config : public obs::Subject<OnConfigParameterChanged>
{
public:
    /// \param configFile The JSON configuration file
    explicit Config(const string &configFile);

    auto &isDebugMode() const { return m_isDebugMode; }

    auto &mapFileName() const { return m_mapFileName; }

    auto &title() const { return m_title; }

    auto &fontFileName() const { return m_fontFileName; }

    auto tileSizeInPx() const { return vec2i(1, 1) * m_tileSizeInPx; }

    auto &noImguiIni() const { return m_noImguiIni; }

    sf::VideoMode videoMode() const;
    sf::Uint32 windowStyle() const;

    /// When debugging is enabled, draw a debugging window to change the useful config parameters on the fly
    /// Some parameters are readen only once, so these need callback or aren't allowed to be modified.
    /// So do not print all parameters
    /// Here print parameters relevant to the config, general parameters usually applicables for any scene
    void showImguiDebugWindow();

private:
    void notifyChange(ConfigParameter parameter);

    vec2i m_windowSize;
    int m_tileSizeInPx; /// Always squared
    bool m_isDebugMode;
    bool m_fullscreen;
    bool m_noImguiIni;
    string m_mapFileName;
    string m_fontFileName;
    string m_title;
};


