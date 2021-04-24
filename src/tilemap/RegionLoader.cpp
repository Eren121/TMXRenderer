#include "tilemap/RegionLoader.hpp"
#include "pokemon/Trainer.hpp"
#include "common.hpp"
#include <fstream>

using namespace std;
using namespace sf;

namespace Tm
{
    RegionLoader::RegionLoader(const string &jsonFile)
    {
        if (!jsonFile.ends_with(".json"))
        {
            throw std::runtime_error("Map file format not recognized: " + jsonFile + ", only JSON is supported.");
        }

        ifstream ifs;
        assets::open(jsonFile, ifs);

        const Json json = Json::parse(ifs);
        const int height = json.at("height").get<int>();
        const int width = json.at("width").get<int>();

        m_region = make_unique<Region>(width, height);

        // Properties of the region
        if (json.contains("properties"))
        {
            const PropertyMap props = Loader::parseProperties(json.at("properties"));

            if (props.contains("tileTypes") && holds_alternative<std::string>(props.at("tileTypes")))
            {
                const std::string filename = get<string>(props.at("tileTypes"));
                loadObjectTypes(filename);
            }
        }
        // Currently only one tileset supported

        const string tileset = json.at("tilesets").at(0).at("source");
        m_tileset = make_unique<Tileset>(tileset);

        loadLayers(json.at("layers"));
    }

    void RegionLoader::loadLayers(const Json &layers)
    {
        for (auto &layer : layers)
        {
            // Add one layer

            m_region->layers().emplace_back(m_region->size());
            auto &back = m_region->layers().back(); // Just added layer

            int x = 0;
            int y = 0;

            if (layer.contains("data"))
            {
                for (int gid : layer.at("data"))
                {
                    // Add each tile of the layer

                    gid--; // Tiled add 1 to allow zero to be the "empty tile".

                    back[{x, y}] = (*m_tileset)[gid];

                    x++;
                    if (x == m_region->width())
                    {
                        y++;
                        x = 0;
                    }
                }
            }

            if (layer.contains("objects"))
            {
                for (auto &objectRef : layer.at("objects"))
                {
                    Json object = objectRef; // Copy for non-const; to add default object type data
                    const string name = object.at("name");
                    const string type = object.at("type");

                    if (!type.empty())
                    {
                        if (m_objTypes.contains(type))
                        {
                            // Add all predefined fields
                            const auto &propertyMap = m_objTypes.at(type);
                            for (auto &prop : propertyMap)
                            {
                                const auto &name = prop.first;
                                const auto &value = prop.second;

                                object[name] = Loader::propertyToJson(value);
                            }
                        }
                        else
                        {
                            cerr << "Warning: unknown object type: " << type << endl;
                        }
                    }

                    if (object.contains("properties"))
                    {
                        auto props = Loader::parseProperties(object.at("properties"));
                        for (auto&&[key, value] : props)
                        {
                            object[key] = Loader::propertyToJson(value);
                        }
                    }

                    vec2f objPos;
                    objPos.x = object.at("x");
                    objPos.y = object.at("y");
                    objPos /= vec2f(m_tileset->tilesize()); // Object position is in pixel, we want in tile
                    const vec2i objPosRounded = vec2i(objPos);

                    auto &registry = m_region->registry();

                    if (type == "PlayerStart")
                    {
                        const Vector2i playerStart = objPosRounded;

                        Vector2i playerSight;
                        playerSight.x = object.at("sightX");
                        playerSight.y = object.at("sightY");

                        cout << "Found player start" << endl;

                        auto player = registry.create();
                        registry.emplace<Position>(player, playerStart);
                        registry.emplace<Character>(player, "Regis");
                        registry.emplace<Player>(player, playerSight);
                    }
                    else if (type == "Character")
                    {
                        auto character = registry.create();
                        registry.emplace<Position>(character, objPosRounded);
                        registry.emplace<Character>(character, name);

                        {
                            const auto &key = "dialog";
                            if (object.contains(key) && object.at(key).is_string())
                            {
                                const std::string &value = object.at(key);
                                registry.emplace<Dialog>(character, value);
                            }
                        }
                        {
                            const bool isTrainer = object.value("trainer", false);
                            if(isTrainer)
                            {
                                registry.emplace<Pkm::Trainer>(character);
                            }
                        }
                    }
                }
            }

            if (layer.contains("properties"))
            {
                const auto props = Loader::parseProperties(layer.at("properties"));
                back.properties() = props;

                for (auto&[k, v] :props)
                {
                    cout << k << endl;
                }

                if (props.contains("scrollX") && holds_alternative<float>(props.at("scrollX")))
                {
                    back.scroll().x = get<float>(props.at("scrollX"));
                }
                if (props.contains("scrollY") && holds_alternative<float>(props.at("scrollY")))
                {
                    back.scroll().y = get<float>(props.at("scrollY"));
                }
            }
        }
    }

    void RegionLoader::loadObjectTypes(const string &filename)
    {
        std::ifstream ifs;
        assets::open(filename, ifs);

        // The file contains an array of all predefined types of objects
        // Each type of object contains an array of properties and their default value

        const Json json = Json::parse(ifs);

        for (auto &type : json)
        {
            const std::string name = type.at("name");
            const PropertyMap props = Loader::parseProperties(type.at("properties"));
            m_objTypes[name] = props;
        }
    }
}