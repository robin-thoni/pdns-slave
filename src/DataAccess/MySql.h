//
// Created by robin on 8/9/15.
//

#ifndef PDNS_SLAVE_MYSQL_H
#define PDNS_SLAVE_MYSQL_H

#include <DBO/Result.h>
#include <DBO/SqlConfiguration.h>
# include "DBO/Result.h"

class MySql
{
public:
    MySql(const SqlConfiguration& masterConfig, const SqlConfiguration& slaveConfig);
    virtual ~MySql();

    BResult dump();

    BResult insert();

    BResult override(const std::string& sql);

    void clean();

private:
    const std::string getTempFile();

    BResult insertSlave(const std::string& file);

    SqlConfiguration _masterConfig;

    SqlConfiguration _slaveConfig;

    std::string _dumpFilePath;

    std::string _overrideFilePath;
};


#endif //PDNS_SLAVE_MYSQL_H
