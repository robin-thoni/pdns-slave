//
// Created by robin on 8/8/15.
//

#include <json/json.h>
#include <fstream>
#include "HostsConfig.h"

HostsConfig::HostsConfig(const std::string &filePath)
    : _filePath(filePath)
{
}

bool HostsConfig::readConfig()
{
    std::ifstream file(_filePath);
    if (!file)
        return false;
    Json::Value root;
    try
    {
        file >> root;
        file.close();
    }
    catch (...)
    {
        file.close();
        return false;
    }
    auto defaults = root["defaults"];
    auto actions = root["actions"];
    for (Json::ArrayIndex i = 0; i < actions.size(); ++i)
    {
        auto action = actions[i];
        auto action_type = readValue(action, defaults, "action");
    }
    return true;
}

Json::Value HostsConfig::readValue(const Json::Value &value, const Json::Value &defaults, const std::string &name)
{
    auto v = value[name];
    if (!v)
        return defaults[name];
    return v;
}
