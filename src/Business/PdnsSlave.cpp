//
// Created by robin on 8/8/15.
//

#include <fstream>
#include "DataAccess/PdnsSlaveConfig.h"
#include "PdnsSlave.h"

PdnsSlave::PdnsSlave(const std::string &filePath)
    : _filePath(filePath)
{
}

bool PdnsSlave::readConfig()
{
    PdnsSlaveConfig conf(_filePath);
    if (!conf.readConfig())
        return false;

    _dhcpdFilePath = conf.getDhcpdFilePath();
    _dhcpdTemplatePath = conf.getDhcpdTemplatePath();
    _hostsPath = conf.getHostsPath();
    _masterConfig = conf.getMasterConfig();
    _slaveConfig = conf.getSlaveConfig();

    return true;
}

bool PdnsSlave::readDhcpdTemplate()
{
    std::ifstream dhcpTemplate(_dhcpdTemplatePath);
    if (!dhcpTemplate)
        return false;
    while (!dhcpTemplate.eof())
    {
        std::string line;
        getline(dhcpTemplate, line);
        _dhcpdTemplateContent += line + "\n";
    }
    dhcpTemplate.close();
    return true;
}
