//
// Created by robin on 8/8/15.
//

#include <json/json.h>
#include <fstream>
#include <memory>
#include <DBO/Actions/Action.h>
#include <DBO/Actions/ActionAddHost.h>
#include <DBO/Actions/ActionDelHost.h>
#include <DBO/Actions/ActionAddDomain.h>
#include <DBO/Actions/ActionDelDomain.h>
#include "HostsConfig.h"

#define SET_VALUE(VALUE, METHOD, TYPE) do {             \
    if (action)                                         \
    {                                                   \
        auto v = readValue(act, defaults, VALUE);       \
        if (!v || !v.is##TYPE())                        \
        {                                               \
            res.addWarning("Could not find value "      \
                VALUE " for item " + std::to_string(i));\
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

Result<Actions> HostsConfig::readConfig()
{
    Result<Actions> res;
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
    if (!defaults || !defaults.isObject())
        return res.error("Could not find defaults object");
    auto acts = root["actions"];
    if (!acts || !acts.isArray())
        return res.error("Could not find actions array");
    std::vector<std::shared_ptr<Action>> actions;
    for (Json::ArrayIndex i = 0; i < acts.size(); ++i)
    {
        auto act = acts[i];
        auto action_type = readValue(act, defaults, "action");
        if (!action_type || !action_type.isString())
            res.addWarning("Could not find action value for item " + std::to_string(i));
        else
        {
            auto action_str = action_type.asString();
            if (action_str == "add_domain")
            {
                auto del = readDelDomain(act, defaults, i, res);
                auto add = readAddDomain(act, defaults, i, res);
                if (del && add)
                {
                    actions.push_back(del);
                    actions.push_back(add);
                }
            }
            else if (action_str == "del_domain")
            {
                auto del = readDelDomain(act, defaults, i, res);
                if (del)
                    actions.push_back(del);
            }
            else if (action_str == "add_host")
            {
                auto del = readDelHost(act, defaults, i, res);
                auto add = readAddHost(act, defaults, i, res);
                if (del && add)
                {
                    actions.push_back(del);
                    actions.push_back(add);
                }
            }
            else if (action_str == "del_host")
            {
                auto del = readDelHost(act, defaults, i, res);
                if (del)
                    actions.push_back(del);
            }
            else
                res.addWarning("Unknown action " + action_str);
        }
    }
    return res.ok(actions);
}

Json::Value HostsConfig::readValue(const Json::Value &value, const Json::Value &defaults, const std::string &name) const
{
    auto v = value[name];
    if (!v)
        return defaults[name];
    return v;
}

std::shared_ptr<Action> HostsConfig::readAddHost(const Json::Value &act, const Json::Value &defaults,
                                                 int i, Result<Actions>& res) const
{
    auto action = std::make_shared<ActionAddHost>();
    SET_VALUE_STRING("domain", setDomain);
    SET_VALUE_STRING("host", setHost);
    SET_VALUE_STRING("record_value", setRecordValue);
    SET_VALUE_STRING("record_type", setRecordType);
    SET_VALUE_STRING("dhcp_mac", setDhcpMac);
    SET_VALUE_STRING("reverse_domain", setReverseDomain);
    SET_VALUE_BOOL("reverse_enabled", setReverseEnabled);
    return action;
}

std::shared_ptr<Action> HostsConfig::readDelHost(const Json::Value &act, const Json::Value &defaults, int i,
                                                 Result<Actions> &res) const
{
    auto action = std::make_shared<ActionDelHost>();
    SET_VALUE_STRING("domain", setDomain);
    SET_VALUE_STRING("host", setHost);
    return action;
}

std::shared_ptr<Action> HostsConfig::readAddDomain(const Json::Value &act, const Json::Value &defaults, int i,
                                                   Result<Actions> &res) const
{
    auto action = std::make_shared<ActionAddDomain>();
    SET_VALUE_STRING("domain", setDomain);
    return action;
}

std::shared_ptr<Action> HostsConfig::readDelDomain(const Json::Value &act, const Json::Value &defaults, int i,
                                                   Result<Actions> &res) const
{
    auto action = std::make_shared<ActionDelDomain>();
    SET_VALUE_STRING("domain", setDomain);
    return action;
}
