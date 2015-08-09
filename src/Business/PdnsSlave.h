//
// Created by robin on 8/8/15.
//

#ifndef PDNS_SLAVE_PDNSSLAVE_H
#define PDNS_SLAVE_PDNSSLAVE_H

# include <string>
# include <memory>
# include "DBO/SqlConfiguration.h"
# include "DBO/Actions/Action.h"

class PdnsSlave
{
public:
    PdnsSlave(const std::string& filePath);

    BResult readConfig();

    BResult readDhcpdTemplate();

    Result<Actions> readHosts();

    BResult overridePdns();

    BResult overrideDhcp();

private:
    std::string _filePath;

    std::string _dhcpdFilePath;

    std::string _dhcpdTemplatePath;

    std::string _hostsPath;

    SqlConfiguration _masterConfig;

    SqlConfiguration _slaveConfig;

    std::string _dhcpdTemplateContent;

    Actions _actions;
};


#endif //PDNS_SLAVE_PDNSSLAVE_H
