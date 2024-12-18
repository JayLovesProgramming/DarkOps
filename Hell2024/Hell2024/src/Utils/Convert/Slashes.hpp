#pragma once

#include <iostream>
#include <algorithm>

std::string ReplaceBackwardSlashesToForward(std::string& str)
{
    std::string stringToConvert(str);

    std::replace(stringToConvert.begin(), stringToConvert.end(), '\\', '/');

    return stringToConvert;
}

std::string ExtractWeaponTypeByDirectory(std::string& str)
{
    std::string stringToConvert(str);

    return "UNKNOWN";
}

std::string ExtractModelName(const std::string& str)
{
    std::filesystem::path path(str);

    std::string filename = path.stem().string();
    if (!filename.empty())
    {
        return filename;
    }

    return str;
}