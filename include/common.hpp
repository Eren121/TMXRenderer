#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <entt/entt.hpp>
#include <magic_enum.hpp>
#include "config/Assets.hpp"
#include "config/Json.hpp"
#include "config/Math.hpp"
#include "config/Time.hpp"
#include "config/Interpolation.hpp"
#include "config/Algorithm.hpp"
#include "config/ECS.hpp"
#include "observer/Observer.hpp"
#include "observer/Subject.hpp"

using namespace magic_enum::ostream_operators;

using std::string;
using std::cout;
using std::endl;
using std::cerr;
using std::max;
using std::min;
using std::clamp;

template<typename T>
using UniquePtr = std::unique_ptr<T>;

template<typename T, typename K, typename V>
auto &getOrDefault(const T &container, const K &key, const V &def)
{
    if (container.contains(key)) return container.at(key);
    else return def;
}

/// @returns the uppercased string
string toUpper(const std::string &str);
