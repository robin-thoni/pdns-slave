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

bool PdnsSlaveConfig::readConfig()
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
    if (!readString(root, "dhcpd-file", _dhcpdFilePath))
        return false;
    if (!readString(root, "dhcpd-template", _dhcpdTemplatePath))
        return false;
    if (!readString(root, "hosts-file", _hostsPath))
        return false;
    if (!readSqlConfiguration(root, "master", _masterConfig))
        return false;
    if (!readSqlConfiguration(root, "slave", _slaveConfig))
        return false;

    return true;
}

bool PdnsSlaveConfig::readSqlConfiguration(const Json::Value &value, const std::string &name, SqlConfiguration &sqlConfiguration)
{
    std::string str;
    if (!readString(value, name + "-host", str))
        return false;
    sqlConfiguration.setHost(str);

    if (!readString(value, name + "-user", str))
        return false;
    sqlConfiguration.setUser(str);

    if (!readString(value, name + "-password", str))
        return false;
    sqlConfiguration.setPassword(str);

    if (!readString(value, name + "-database", str))
        return false;
    sqlConfiguration.setDatabase(str);

    return true;
}

bool PdnsSlaveConfig::readString(const Json::Value &value, const std::string &name, std::string &dest)
{
    auto v = value[name];
    if (!v)
        return false;
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