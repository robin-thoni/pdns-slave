//
// Created by robin on 8/9/15.
//

#ifndef PDNS_SLAVE_MYSQL_H
#define PDNS_SLAVE_MYSQL_H

#include "AbstractSql.h"

class MySql : public AbstractSql
{
public:
    MySql(const SqlConfiguration& masterConfig, const SqlConfiguration& slaveConfig);
    ~MySql();

    BResult dump();

    BResult insert();

    BResult override(const std::string& sql);

private:
    const std::string getTempFile();

    BResult insertSlave(const std::string& file);

    std::string _dumpFilePath;

    std::string _overrideFilePath;
};


#endif //PDNS_SLAVE_MYSQL_H
