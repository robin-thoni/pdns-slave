//
// Created by robin on 8/8/15.
//

#ifndef PDNS_SLAVE_HOSTSCONFIG_H
#define PDNS_SLAVE_HOSTSCONFIG_H

# include <string>
# include "DBO/Result.h"
# include "DBO/Actions/Action.h"

class HostsConfig
{
public:
    HostsConfig(const std::string& filePath);

    Result<Actions> readConfig();

private:
    Json::Value readValue(const Json::Value &value, const Json::Value &defaults, const std::string& name) const;

    std::shared_ptr<Action> readAddHost(const Json::Value &act, const Json::Value &defaults,
                                        int i, Result<Actions>& res) const;

    std::shared_ptr<Action> readDelHost(const Json::Value &act, const Json::Value &defaults,
                                        int i, Result<Actions>& res) const;

    std::shared_ptr<Action> readAddDomain(const Json::Value &act, const Json::Value &defaults,
                                        int i, Result<Actions>& res) const;

    std::shared_ptr<Action> readDelDomain(const Json::Value &act, const Json::Value &defaults,
                                        int i, Result<Actions>& res) const;

    std::string _filePath;
};


#endif //PDNS_SLAVE_HOSTSCONFIG_H
