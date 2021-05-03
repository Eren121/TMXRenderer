#include "tilemap/Property.hpp"

namespace Tm
{
    PropertiesMap Property::asMap(const std::vector<tmx::Property> &properties)
    {
        PropertiesMap map;

        for (const auto &tmx_prop : properties)
        {
            Property prop(tmx_prop);
            map[prop.name] = prop;
        }

        return map;
    }

    PropertiesMap Property::asMap(const Json &properties)
    {
        PropertiesMap map;

        for (const auto &j_prop : properties)
        {
            Property prop(j_prop);
            map[prop.name] = prop;
        }

        return map;
    }

    Property::Property(const tmx::Property &other)
        : name(other.getName()),
          type(other.getType())
    {
        using Type = tmx::Property::Type;

        switch (other.getType())
        {
            case Type::Boolean:
                variant = other.getBoolValue();
                break;
            case Type::Float:
                variant = other.getFloatValue();
                break;
            case Type::Int:
                variant = other.getIntValue();
                break;
            case Type::String:
                variant = other.getStringValue();
                break;
            case Type::Colour:
                variant = other.getColourValue();
                break;
            case Type::File:
                variant = other.getFileValue();
                break;
            case Type::Object:
                variant = other.getObjectValue();
                break;

            case Type::Undef:
            default:
                cerr << "Warning: unkown property" << endl;
                break;
        }
    }

    Property::Property(const Json &other)
        : name(other.value("name", ""))
    {
        string j_type = other.value("type", "");
        const auto &j_value = other.at("value");

        if ((j_type == "string" || j_type == "file") && j_value.is_string())
        {
            variant = string(j_value);
            type = Type::String;
        }
        else if (j_type == "int" && j_value.is_number())
        {
            variant = int(j_value);
            type = Type::Int;
        }
        else if (j_type == "float" && j_value.is_number())
        {
            variant = float(j_value);
            type = Type::Float;
        }
        else if (j_type == "bool" && j_value.is_boolean())
        {
            variant = bool(j_value);
            type = Type::Boolean;
        }
        else
        {
            cerr << "Property type not recognized: " << j_type << endl;
        }
    }

    bool Property::getOrDefault(const PropertiesMap &props, const string &name, bool def)
    {
        auto ret(def);

        if (props.contains(name))
        {
            const auto &prop = props.at(name);
            if (prop.type == tmx::Property::Type::Boolean)
            {
                ret = get<bool>(prop.variant);
            }
        }

        return ret;
    }

    float Property::getOrDefault(const PropertiesMap &props, const string &name, float def)
    {
        auto ret(def);

        if (props.contains(name))
        {
            const auto &prop = props.at(name);
            if (prop.type == tmx::Property::Type::Float)
            {
                ret = get<float>(prop.variant);
            }
            else if (prop.type == tmx::Property::Type::Int)
            {
                ret = get<int>(prop.variant);
            }
        }

        return ret;
    }

    int Property::getOrDefault(const PropertiesMap &props, const string &name, int def)
    {
        auto ret(def);

        if (props.contains(name))
        {
            const auto &prop = props.at(name);
            if (prop.type == tmx::Property::Type::Int)
            {
                ret = get<int>(prop.variant);
            }
            else if (prop.type == tmx::Property::Type::Float)
            {
                ret = get<float>(prop.variant);
                cerr << "warning: float property returned as int: " << name << endl;
            }
        }

        return ret;
    }

    const string &Property::getOrDefault(const PropertiesMap &props, const string &name, const string &def)
    {
        if (props.contains(name))
        {
            const auto &prop = props.at(name);
            if (prop.type == tmx::Property::Type::String)
            {
                return get<string>(prop.variant);
            }
            else if (prop.type == tmx::Property::Type::File)
            {
                return get<string>(prop.variant);
            }
        }

        return def;
    }

    string Property::getOrDefault(const PropertiesMap &props, const string &name, const char *def)
    {
        return getOrDefault(props, name, string(def));
    }

    tmx::Colour Property::getOrDefault(const PropertiesMap &props, const string &name, tmx::Colour def)
    {
        auto ret(def);

        if (props.contains(name))
        {
            const auto &prop = props.at(name);
            if (prop.type == tmx::Property::Type::Colour)
            {
                ret = get<tmx::Colour>(prop.variant);
            }
        }

        return ret;
    }

    Direction Property::getOrDefault(const PropertiesMap &props, const string &name, Direction def)
    {
        auto ret(def);
        auto str_direction = getOrDefault(props, name, string(magic_enum::enum_name(def)));
        auto optional_direction = magic_enum::enum_cast<Direction>(toUpper(str_direction));

        if(optional_direction.has_value())
        {
            ret = optional_direction.value();
        }

        return ret;
    }
}