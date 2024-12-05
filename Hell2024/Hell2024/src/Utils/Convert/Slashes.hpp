#pragma once

#include <iostream>
#include <algorithm>

std::string ReplaceBackwardSlashesToForward(std::string& str)
{
    std::string stringToConvert(str);

    std::replace(stringToConvert.begin(), stringToConvert.end(), '\\', '/');

    return stringToConvert;
}