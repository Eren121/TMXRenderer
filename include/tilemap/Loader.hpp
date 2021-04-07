#pragma once

#include "common.hpp"
#include <variant>

namespace Tm
{
    using Property = std::variant<std::string, int, float, bool>;
    using PropertyMap = std::map<std::string, Property>;

    /**
     * @brief Various utility function for parsing TSX and TMX files.
     */
    class Loader
    {
    public:
        static PropertyMap parseProperties(const Json &properties);
        static Json propertyToJson(const Property& property);
    };
}