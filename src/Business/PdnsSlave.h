//
// Created by robin on 8/8/15.
//

#ifndef PDNS_SLAVE_PDNSSLAVE_H
#define PDNS_SLAVE_PDNSSLAVE_H

# include <string>
# include "DBO/SqlConfiguration.h"

class PdnsSlave
{
public:
    PdnsSlave(const std::string& filePath);

    bool readConfig();

    bool readDhcpdTemplate();

private:
    std::string _filePath;

    std::string _dhcpdFilePath;

    std::string _dhcpdTemplatePath;

    std::string _hostsPath;

    SqlConfiguration _masterConfig;

    SqlConfiguration _slaveConfig;

    std::string _dhcpdTemplateContent;
};


#endif //PDNS_SLAVE_PDNSSLAVE_H
