//
// Created by robin on 8/8/15.
//

#include <fstream>
#include <iostream>
# include <json/json.h>
#include "PdnsSlaveConfig.h"

PdnsSlaveConfig::PdnsSlaveConfig(const std::string &filePath)
    : _filePath(filePath)
{
}

BResult PdnsSlaveConfig::readConfig()
{
    std::ifstream file(_filePath);
    if (!file)
        return BResult().error("Could not open file");
    Json::Value root;
    try
    {
        file >> root;
        file.close();
    }
    catch (...)
    {
        file.close();
        return BResult().error("Could not parse JSON");
    }
    BResult res;
    if (!(res = readString(root, "dhcpd-file", _dhcpdFilePath)))
        return res;
    if (!(res = readString(root, "dhcpd-template", _dhcpdTemplatePath)))
        return res;
    if (!(res = readString(root, "hosts-file", _hostsPath)))
        return res;
    if (!(res = readSqlConfiguration(root, "master", _masterConfig)))
        return res;
    if (!(res = readSqlConfiguration(root, "slave", _slaveConfig)))
        return res;
    return true;
}

BResult PdnsSlaveConfig::readSqlConfiguration(const Json::Value &value, const std::string &name, SqlConfiguration &sqlConfiguration)
{
    std::string str;
    BResult res;
    if (!(res = readString(value, name + "-host", str)))
        return res;
    sqlConfiguration.setHost(str);

    if (!(res = readString(value, name + "-user", str)))
        return res;
    sqlConfiguration.setUser(str);

    if (!(res = readString(value, name + "-password", str)))
        return res;
    sqlConfiguration.setPassword(str);

    if (!(res = readString(value, name + "-database", str)))
        return res;
    sqlConfiguration.setDatabase(str);

    return true;
}

BResult PdnsSlaveConfig::readString(const Json::Value &value, const std::string &name, std::string &dest)
{
    auto v = value[name];
    if (!v)
        return BResult().error("Could not find value " + name);
    dest = v.asString();
    return true;
}

const std::string &PdnsSlaveConfig::getDhcpdFilePath() const
{
    return _dhcpdFilePath;
}

const std::string &PdnsSlaveConfig::getDhcpdTemplatePath() const
{
    return _dhcpdTemplatePath;
}

const std::string &PdnsSlaveConfig::getHostsPath() const
{
    return _hostsPath;
}

const SqlConfiguration &PdnsSlaveConfig::getMasterConfig() const
{
    return _masterConfig;
}

const SqlConfiguration &PdnsSlaveConfig::getSlaveConfig() const
{
    return _slaveConfig;
}