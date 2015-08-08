//
// Created by robin on 8/8/15.
//

#ifndef PDNS_SLAVE_PDNSSLAVECONFIG_H
#define PDNS_SLAVE_PDNSSLAVECONFIG_H

# include <string>
# include "DBO/SqlConfiguration.h"

namespace Json
{
    class Value;
}

class PdnsSlaveConfig
{
public:
    PdnsSlaveConfig(const std::string& filePath);

    bool readConfig();

    const std::string &getDhcpdFilePath() const;

    const std::string &getDhcpdTemplatePath() const;

    const std::string &getHostsPath() const;

    const SqlConfiguration &getMasterConfig() const;

    const SqlConfiguration &getSlaveConfig() const;

private:
    bool readString(const Json::Value& value, const std::string& name, std::string& dest);

    bool readSqlConfiguration(const Json::Value &value, const std::string &name, SqlConfiguration& sqlConfiguration);

    std::string _filePath;

private:
    std::string _dhcpdFilePath;

    std::string _dhcpdTemplatePath;

    std::string _hostsPath;

    SqlConfiguration _masterConfig;

    SqlConfiguration _slaveConfig;
};


#endif //PDNS_SLAVE_PDNSSLAVECONFIG_H
