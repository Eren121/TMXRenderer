#pragma once

#include "common.hpp"
#include "Region.hpp"
#include <tmxlite/Map.hpp>
#include "Tileset.hpp"
#include "Property.hpp"
#include "LayerOfTiles.hpp"
#include "LayerOfObjects.hpp"

namespace Tm
{
    /**
     * @brief To load a map before conversion to region class.
     */
    class RegionLoader
    {
    public:
        /**
         * @brief Load a region from a file.
         * @param mapFile The file in the TMX JSON Map Format.
         * @see https://doc.mapeditor.org/en/stable/reference/json-map-format/
         */
        RegionLoader(const string &mapFile);
        ~RegionLoader() = default;

        auto &region()
        {
            assert(m_region);
            return *m_region;
        }

        auto &tileset() const { return m_tileset; }

    private:
        void loadLayers();
        void loadObjectTypes(const std::string &filename);
        void loadObjectLayer(LayerOfObjects &into, const tmx::ObjectGroup &tmx_layer);
        void loadTileLayer(LayerOfTiles &into, const tmx::TileLayer &tmx_layer);

        /// Add default
        /// Do not overwrite existing properties
        void updateObjectPropertiesFromType(PropertiesMap &objectProps, const string &type);

    private:
        /// The result region loaded
        std::unique_ptr<Region> m_region;

        /// Predefined properties for the object of the type of the key
        std::map<string, PropertiesMap> m_objTypes;

        tmx::Map m_map;

        Tileset m_tileset;
    };
}