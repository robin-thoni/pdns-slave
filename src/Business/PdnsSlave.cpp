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

BResult PdnsSlave::readConfig()
{
    PdnsSlaveConfig conf(_filePath);
    BResult res;
    if (!(res = conf.readConfig()))
        return res;

    _dhcpdFilePath = conf.getDhcpdFilePath();
    _dhcpdTemplatePath = conf.getDhcpdTemplatePath();
    _hostsPath = conf.getHostsPath();
    _masterConfig = conf.getMasterConfig();
    _slaveConfig = conf.getSlaveConfig();

    return true;
}

BResult PdnsSlave::readDhcpdTemplate()
{
    std::ifstream dhcpTemplate(_dhcpdTemplatePath);
    if (!dhcpTemplate)
        return BResult().error("Could not open file");
    while (!dhcpTemplate.eof())
    {
        std::string line;
        getline(dhcpTemplate, line);
        _dhcpdTemplateContent += line + "\n";
    }
    dhcpTemplate.close();
    return true;
}
