#include "tilemap/Tileset.hpp"

using namespace std;
using namespace sf;

namespace Tm
{

    Tileset::Tileset(const string &tilesetJson)
    {
        if (!tilesetJson.ends_with(".json"))
        {
            throw runtime_error("Tileset file format not recognized: " + tilesetJson + ", only JSON is supported.");
        }

        ifstream ifs;
        assets::open(tilesetJson, ifs);

        const Json json = Json::parse(ifs);

#define readAttribute(name) m_##name = json.at(#name)
        readAttribute(columns);
        readAttribute(image);
        readAttribute(margin);
        readAttribute(name);
        readAttribute(spacing);
        readAttribute(tilecount);
        readAttribute(tileheight);
        readAttribute(tilewidth);

        loadTiles(json.at("tiles"));
    }

    void Tileset::loadTiles(const Json &tiles)
    {
        Vector2i atlasPos;

        for (auto &tile : tiles)
        {
            // Get tile properties
            const int id = tile.at("id");
            const string name = to_string(id);
            const auto properties = Loader::parseProperties(tile.at("properties"));
            const bool walkable = getProperty(properties, "walkable", false);

            // Insert tile
            m_tiles[id] = make_unique<TileType>(name, walkable, atlasPos);

            // Update atlas position
            atlasPos.x++;
            if (atlasPos.x == columns())
            {
                atlasPos.x = 0;
                atlasPos.y++;
            }
        }
    }

    const TileType *Tileset::operator[](int gid) const
    {
        const auto it = m_tiles.find(gid);
        if (it == m_tiles.end())
        {
            return nullptr;
        }
        else
        {
            return it->second.get();
        }
    }
}