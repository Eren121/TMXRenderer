#pragma once

#include "Direction.hpp"
#include "common.hpp"
#include <tmxlite/Property.hpp>
#include <variant>

namespace Tm
{
    class Property;
    using PropertiesMap = std::map<string, Property>;

    class Property
    {
    public:
        using Variant = std::variant<bool, int, float, string, tmx::Colour>;
        using Type = tmx::Property::Type;

        /// Convenient function
        /// And also O(1) lookup instead of iterating each time to get a property...
        static PropertiesMap asMap(const std::vector<tmx::Property> &properties);

        /// Parse JSON properties
        /// For object types file
        static PropertiesMap asMap(const Json &properties);

        static bool getOrDefault(const PropertiesMap &props, const string &name, bool def);
        static float getOrDefault(const PropertiesMap &props, const string &name, float def);
        static int getOrDefault(const PropertiesMap &props, const string &name, int def);
        static const string& getOrDefault(const PropertiesMap &props, const string &name, const string& def);
        static string getOrDefault(const PropertiesMap &props, const string &name, const char *def); // String
        static tmx::Colour getOrDefault(const PropertiesMap &props, const string &name, tmx::Colour def);

        static Direction getOrDefault(const PropertiesMap &props, const string &name, Direction def); // Also string

        Property() = default;
        Property(const tmx::Property& other);
        Property(const Json &other);

        string name;
        Type type = Type::Undef;
        Variant variant;
    };
}

