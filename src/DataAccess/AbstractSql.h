//
// Created by robin on 4/6/16.
//

#ifndef PDNS_SLAVE_ABSTRACTSQL_H
#define PDNS_SLAVE_ABSTRACTSQL_H

#include <DBO/Result.h>
#include <DBO/SqlConfiguration.h>
#include "DBO/Result.h"

class AbstractSql
{
public:
    AbstractSql(const SqlConfiguration& masterConfig, const SqlConfiguration& slaveConfig);
    virtual ~AbstractSql();

    virtual BResult dump() = 0;

    virtual BResult insert() = 0;

    virtual BResult override(const std::string& sql) = 0;

protected:
    SqlConfiguration _masterConfig;

    SqlConfiguration _slaveConfig;
};


#endif //PDNS_SLAVE_ABSTRACTSQL_H
