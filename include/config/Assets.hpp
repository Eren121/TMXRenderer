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

    inline std::string getFileName(const std::string &path)
    {
        return directory() + path;
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