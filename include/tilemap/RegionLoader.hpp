#pragma once

#include "common.hpp"
#include "Region.hpp"
#include "Tileset.hpp"
#include "Loader.hpp"

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
         * @param jsonFile The file in the TMX JSON Map Format.
         * @see https://doc.mapeditor.org/en/stable/reference/json-map-format/
         */
        RegionLoader(const string &jsonFile);
        ~RegionLoader() = default;

        Region& region() { return *m_region; }

    private:
        void loadLayers(const Json &layers);
        void loadObjectTypes(const std::string &filename);

    private:
        /// The result region loaded
        std::unique_ptr<Region> m_region;
        std::unique_ptr<Tileset> m_tileset;

        std::map<std::string, PropertyMap> m_objTypes;
    };
}