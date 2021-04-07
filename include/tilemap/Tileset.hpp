#pragma once

#include <variant>
#include "common.hpp"
#include "TileType.hpp"
#include "Loader.hpp"

namespace Tm
{
    class Tileset
    {
    public:
        Tileset(const std::string &tilesetJson);
        ~Tileset() = default;

        int columns() const { return m_columns; }

        const string &image() const { return m_image; }

        int margin() const { return m_margin; }

        const string &name() const { return m_name; }

        int spacing() const { return m_spacing; }

        int tilecount() const { return m_tilecount; }

        int tileheight() const { return m_tileheight; }

        int tilewidth() const { return m_tilewidth; }

        sf::Vector2i tilesize() const { return {m_tilewidth, m_tileheight}; }

        const TileType *operator[](int gid) const;

    private:
        void loadTiles(const Json &tiles);

        template<typename T>
        T getProperty(const PropertyMap &map, const std::string &key, T def)
        {
            const auto it = map.find(key);
            if (it == map.end())
            {
                return def;
            }

            // Get only if it's the right type
            const auto &val = it->second;
            if (std::holds_alternative<T>(val))
            {
                return std::get<T>(val);
            }
            else
            {
                return def;
            }
        }

    private:
        int m_columns;
        string m_image;
        int m_margin;
        string m_name;
        int m_spacing;
        int m_tilecount;
        int m_tileheight;
        int m_tilewidth;

        std::map<int, std::unique_ptr<TileType>> m_tiles;
    };
}


