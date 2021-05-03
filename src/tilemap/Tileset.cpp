#include "tilemap/Tileset.hpp"
#include <fmt/core.h>
#include <fmt/ostream.h>

using namespace std;
using namespace sf;

namespace Tm
{
    Tileset::Tileset() = default;

    const TileType &Tileset::operator[](int gid) const
    {
        const auto it = m_tiles.find(gid);
        assert(it != m_tiles.end());
        return it->second;
    }

    void Tileset::create(const vector<tmx::Tileset> &tmx_tilesets)
    {
        m_tmx_tilesets = tmx_tilesets;

        for(auto &tmx_tileset : m_tmx_tilesets)
        {
            fmt::print("loading tileset {} (gid {}-{})\n",
                       tmx_tileset.getName(), tmx_tileset.getFirstGID(), tmx_tileset.getLastGID());

            for(auto &tmx_tile : tmx_tileset.getTiles())
            {
                // Get TileType property
                PropertiesMap props = Property::asMap(tmx_tile.properties);
                const string &type = tmx_tile.type;

                // Each tileset has local tile id (LID) in interval [ 0; tiles_count ]
                // But each tileset has also a firstGID property
                // from a LID to a GID, you just has to add firstGID
                // So the GID is guaranteed to be unique

                const int gid = int(tmx_tileset.getFirstGID() + tmx_tile.ID);
                m_tiles[gid] = TileType(tmx_tile, tmx_tileset);

                // If the tile is for a character, remember it
                if(type == "T_Character")
                {
                    const auto& character_class = Property::getOrDefault(props, "class", "");
                    const auto& direction = Property::getOrDefault(props, "direction", Direction::DOWN);
                    bool moving = Property::getOrDefault(props, "moving", false);

                    auto key = make_tuple(character_class, direction, moving);
                    if(m_charactersTile.contains(key))
                    {
                        cerr << "warning: duplicate tile for a character (ignored): ";
                        cerr << character_class << ":" << direction << ":" << moving << endl;
                    }
                    else
                    {
                        m_charactersTile[key] = gid;
                    }
                }
            }
        }
    }

    GID Tileset::getCharacterTile(const string &objectType, Direction direction, bool isMoving) const
    {
        const int gid = getOrDefault(m_charactersTile, std::make_tuple(objectType, direction, isMoving), 0);
        return gid;
    }
}