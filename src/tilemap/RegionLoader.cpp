#include "tilemap/RegionLoader.hpp"
#include "pokemon/Trainer.hpp"
#include "config/Iterator2D.hpp"
#include "common.hpp"
#include <fstream>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

using namespace std;
using namespace sf;

namespace Tm
{
    RegionLoader::RegionLoader(const string &mapFile)
    {
        if (!m_map.load(mapFile))
        {
            throw std::runtime_error("Map file format not recognized: " + mapFile + ", tmxlite loading failed.");
        }

        const int width = m_map.getTileCount().x;
        const int height = m_map.getTileCount().y;
        m_region = make_unique<Region>(width, height);

        /// Load tiles (maps each GID to a tile)
        m_tileset.create(m_map.getTilesets());

        loadObjectTypes(assets::getFilePath("object_types.json"));
        loadLayers();
    }

    void RegionLoader::loadLayers()
    {
        // TMX quickstart:
        // https://github.com/fallahn/tmxlite/wiki/Quick-Start

        const auto &tmx_layers = m_map.getLayers();
        for (const auto &tmx_layer : tmx_layers)
        {
            // Add one layer
            // We should differentiate which layer type while adding one
            // Because the class is different

            if (tmx_layer->getType() == tmx::Layer::Type::Object)
            {
                // The layer is an object layer
                const auto &layer = new LayerOfObjects(*m_region);
                m_region->layers().emplace_back(layer);

                const auto &tmx_objectLayer = tmx_layer->getLayerAs<tmx::ObjectGroup>();
                loadObjectLayer(*layer, tmx_objectLayer);
            }
            else if (tmx_layer->getType() == tmx::Layer::Type::Tile)
            {
                // The layer is a tile layer
                const auto &layer = new LayerOfTiles(m_region->size());
                m_region->layers().emplace_back(layer);

                const auto &tmx_tileLayer = tmx_layer->getLayerAs<tmx::TileLayer>();
                loadTileLayer(*layer, tmx_tileLayer);
            }
            else
            {
                cerr << "Warning: unknown layer type in tileset: " << tmx_layer->getName() << endl;
            }

            // Set the properties of the layer independant of type
            auto &justAddedLayer = m_region->layers().back();
            justAddedLayer->setName(tmx_layer->getName());
        }
    }

    void RegionLoader::loadObjectTypes(const string &filename)
    {
        std::ifstream ifs;
        assets::open(filename, ifs);

        // The file contains an array of all predefined types of objects
        // Each type of object contains an array of properties and their default value

        const Json json = Json::parse(ifs);

        for (const auto &j_type : json)
        {
            const std::string name = j_type.at("name");
            const PropertiesMap props = Property::asMap(j_type.at("properties"));
            m_objTypes[name] = props;
        }
    }

    void RegionLoader::loadTileLayer(LayerOfTiles &into, const tmx::TileLayer &tmx_layer)
    {
        // The layer is a tile layer
        const auto &tiles = tmx_layer.getTiles();

        // Position of the tile in world coordinates
        // Iterate to right, then to down
        Iterator2D it(m_region->size());

        for (const auto &tile : tiles)
        {
            GID gid = tile.ID;

            // When gid is zero, that mean the world location is empty (no tile)
            if(gid != 0)
            {
                if(m_tileset.contains(gid))
                {
                    into[*it] = &m_tileset[gid];
                }
                else
                {
                    cerr << "warning: unkown GID " << gid << " at position " << *it << endl;
                }
            }

            ++it;
        }
    }

    void RegionLoader::loadObjectLayer(LayerOfObjects &into, const tmx::ObjectGroup &tmx_layer)
    {
        // Load all objects: trainers, etc...
        // Mostly dynamic elements

        for (const tmx::Object &object : tmx_layer.getObjects())
        {
            PropertiesMap props = Property::asMap(object.getProperties());
            const string &name = object.getName();
            const string &type = object.getType();

            // Add default object type data
            // If it has a predefined type
            updateObjectPropertiesFromType(props, type);

            // Position of the object in world coordinates
            // We must scale because getPosition() returns position in pixels
            vec2f objPos;
            objPos.x = object.getPosition().x;
            objPos.y = object.getPosition().y;
            objPos /= vec2f(m_map.getTileSize().x, m_map.getTileSize().y);
            const vec2i objPosRounded = vec2i(objPos);

            auto &registry = m_region->registry();

            if (type == "PlayerStart")
            {
                const Vector2i playerStart = objPosRounded;

                cout << "Found player start" << endl;

                auto player = registry.create();
                registry.emplace<Position>(player, playerStart);
                auto &character = registry.emplace<Character>(player, "Regis");
                character.speed = sf::milliseconds(Property::getOrDefault(props, "speed", 200.0f));
                registry.emplace<Player>(player);


                // Load player spritesheet
                auto& sprite = registry.emplace<Sprite>(player);

                for(Direction direction : magic_enum::enum_values<Direction>())
                {
                    const GID gid = m_tileset.getCharacterTile("player", direction, false);
                    const GID gidMoving = m_tileset.getCharacterTile("player", direction, true);

                    sprite.gids[direction] = gid;
                    sprite.gidsMoving[direction] = gidMoving;
                }

                // Add the player in the same layer where he was found
                into.addEntity(player);
            }
            else if (type == "Character")
            {
                auto character = registry.create();
                registry.emplace<Position>(character, objPosRounded);
                registry.emplace<Character>(character, name);

                string dialog = Property::getOrDefault(props, "dialog", "");
                if (!dialog.empty())
                {
                    registry.emplace<Dialog>(character, dialog);
                }

                const bool isTrainer = Property::getOrDefault(props, "trainer", false);
                if (isTrainer)
                {
                    registry.emplace<Pkm::Trainer>(character);
                }

                // Characters have a sprite
                auto &sprite = registry.emplace<Sprite>(character);
                for(Direction direction : magic_enum::enum_values<Direction>())
                {
                    const GID gid = m_tileset.getCharacterTile("citizen", direction, false);
                    const GID gidMoving = m_tileset.getCharacterTile("citizen", direction, true);

                    sprite.gids[direction] = gid;
                    sprite.gidsMoving[direction] = gidMoving;
                }

                // Add the character in the same layer where he was found
                into.addEntity(character);
            }
        }
    }

    void RegionLoader
    ::updateObjectPropertiesFromType(PropertiesMap &objectProps, const string &type)
    {
        if(m_objTypes.contains(type))
        {
            for(const auto &[name, prop] : m_objTypes.at(type))
            {
                if(!objectProps.contains(name))
                {
                    objectProps[name] = prop;
                }
            }
        }
        else if(!type.empty())
        {
            cerr << "Warning: unkown object type " << type << endl;
        }
        else
        {
            cerr << "Warning: object has empty type" << endl;
        }
    }
}