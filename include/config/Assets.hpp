#pragma once

#include <string>
#include <fstream>
#include <stdexcept>

namespace assets
{
    inline std::string directory()
    {
        return "../assets/";
    }

    inline std::string getFilePath(const std::string &name)
    {
        return directory() + name;
    }

    inline void open(const std::string &path, std::ifstream &ifs)
    {
        ifs.open(directory() + path);

        if (!ifs)
        {
            throw std::runtime_error("Failed to open " + path);
        }
    }
}