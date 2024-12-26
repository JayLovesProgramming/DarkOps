#include "JSON.hpp"

void JSONObject::WriteString(std::string elementName, std::string value)
{
    data[elementName] = value;
}

void JSONObject::WriteInt(std::string elementName, int value)
{
    data[elementName] = value;
}

void JSONObject::WriteFloat(std::string elementName, float value)
{
    data[elementName] = value;
}

void JSONObject::WriteArray(std::string elementName, std::vector<std::string> value)
{
    data[elementName] = value;
}

std::string JSONObject::GetJSONAsString()
{
    int indent = 4;
    return data.dump(indent);
}

void JSONObject::SaveToFile(std::string filepath)
{
    std::ofstream out(filepath);
    out << GetJSONAsString();
    out.close();
}