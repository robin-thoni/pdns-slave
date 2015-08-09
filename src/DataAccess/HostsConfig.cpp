//
// Created by robin on 8/8/15.
//

#include <json/json.h>
#include <fstream>
#include <memory>
#include <DBO/Actions/Action.h>
#include <DBO/Actions/ActionAddHost.h>
#include <DBO/Actions/ActionDelHost.h>
#include "HostsConfig.h"

#define SET_VALUE(VALUE, METHOD, TYPE) do {             \
    if (action)                                         \
    {                                                   \
        auto v = readValue(act, defaults, VALUE);       \
        if (!v || !v.is##TYPE())                        \
        {                                               \
            action = nullptr;                           \
        }                                               \
        else                                            \
        {                                               \
            action->METHOD(v.as##TYPE());               \
        }                                               \
    }                                                   \
    } while (0)

#define SET_VALUE_STRING(VALUE, METHOD) SET_VALUE(VALUE, METHOD, String)

#define SET_VALUE_BOOL(VALUE, METHOD) SET_VALUE(VALUE, METHOD, Bool)

HostsConfig::HostsConfig(const std::string &filePath)
    : _filePath(filePath)
{
}

BResult HostsConfig::readConfig()
{
    BResult res;
    std::ifstream file(_filePath);
    if (!file)
        return res.error("Could not open file");
    Json::Value root;
    try
    {
        file >> root;
        file.close();
    }
    catch (...)
    {
        file.close();
        return res.error("Could not parse JSON");
    }
    auto defaults = root["defaults"];
    auto actions = root["actions"];
    for (Json::ArrayIndex i = 0; i < actions.size(); ++i)
    {
        auto act = actions[i];
        auto action_type = readValue(act, defaults, "action");
        if (!action_type)
            res.addWarning("Could no find action value for item " + i);
        else
        {
            auto action_str = action_type.asString();
            std::shared_ptr<Action> actionAbs = nullptr;
            if (action_str == "add_domain")
            {

            }
            else if (action_str == "del_domain")
            {

            }
            else if (action_str == "add_host")
            {
                auto action = std::make_shared<ActionAddHost>();
                SET_VALUE_STRING("host", setHost);
                SET_VALUE_STRING("record_value", setRecordValue);
                SET_VALUE_STRING("record_type", setRecordType);
                actionAbs = action;
            }
            else if (action_str == "del_host")
            {
                auto action = std::make_shared<ActionDelHost>();
                SET_VALUE_STRING("host", setHost);
                actionAbs = action;
            }
            else
                res.addWarning("Unkown action " + action_str);
            if (actionAbs)
            {
                auto action = actionAbs;
                SET_VALUE_STRING("domain", setDomain);
            }
            else
                res.addWarning("Errors occured while processing item " + i);
        }
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
