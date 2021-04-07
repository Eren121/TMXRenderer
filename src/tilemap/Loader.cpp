
#include "tilemap/Loader.hpp"

namespace Tm
{
    PropertyMap Loader::parseProperties(const Json &properties)
    {
        PropertyMap map;

        for (auto &prop : properties)
        {
            const string name = prop.at("name");
            const string type = prop.at("type");
            const auto value = prop.at("value");

            if ((type == "string" || type == "file") && value.is_string())
            {
                map[name] = string(value);
            }
            else if (type == "int" && value.is_number_integer())
            {
                map[name] = int(value);
            }
            else if (type == "float" && value.is_number_float())
            {
                map[name] = float(value);
            }
            else if (type == "bool" && value.is_boolean())
            {
                map[name] = bool(value);
            }
            else
            {
                cerr << "Property type not recognized: " << type << endl;
                continue;
            }
        }

        return map;
    }

    Json Loader::propertyToJson(const Property &property)
    {
        Json ret;

        const auto visitor = [&](const auto& value) {
            ret = value;
        };

        std::visit(visitor, property);

        return ret;
    }
}
