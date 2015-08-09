//
// Created by robin on 8/8/15.
//

#include <fstream>
#include "DataAccess/PdnsSlaveConfig.h"
#include "DataAccess/HostsConfig.h"
#include "PdnsSlave.h"

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

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

Result<Actions> PdnsSlave::readHosts()
{
    HostsConfig conf(_hostsPath);
    auto res = conf.readConfig();
    if (!res)
        return res;
    _actions = res.getData();
    return res;
}

BResult PdnsSlave::overridePdns()
{
    return true;
}

BResult PdnsSlave::overrideDhcp()
{
    std::string hosts;
    for (auto a : _actions)
        hosts += a->getDhcpConf();

    auto dhcp = _dhcpdTemplateContent;
    replace(dhcp, "%%HOSTS%%", hosts);
    std::ofstream file(_dhcpdFilePath);
    if (!file)
        return BResult().error("Could not open file");
    file << dhcp;
    file.close();
    return true;
}
