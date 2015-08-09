//
// Created by robin on 8/8/15.
//

#ifndef PDNS_SLAVE_HOSTSCONFIG_H
#define PDNS_SLAVE_HOSTSCONFIG_H

# include <string>
# include <DBO/Result.h>

class HostsConfig
{
public:
    HostsConfig(const std::string& filePath);

    BResult readConfig();

private:
    Json::Value readValue(const Json::Value &value, const Json::Value &defaults, const std::string& name);
    std::string _filePath;
};


#endif //PDNS_SLAVE_HOSTSCONFIG_H
