//
// Created by robin on 4/6/16.
//

#ifndef PDNS_SLAVE_ABSTRACTSQL_H
#define PDNS_SLAVE_ABSTRACTSQL_H

#include <DBO/Result.h>
#include <DBO/SqlConfiguration.h>
#include <DBO/Actions/ActionAddDomain.h>
#include <DBO/Actions/ActionAddHost.h>
#include <DBO/Actions/ActionDelDomain.h>
#include <DBO/Actions/ActionDelHost.h>
#include "DBO/Result.h"

class AbstractSql
{
public:
    AbstractSql(const SqlConfiguration& masterConfig, const SqlConfiguration& slaveConfig);
    virtual ~AbstractSql();

    virtual BResult dump() = 0;

    virtual BResult insert() = 0;

    virtual BResult override(const std::string& sql) = 0;

    virtual std::string getAddDomainQuery(const ActionAddDomain& action) = 0;

    virtual std::string getAddHostQuery(const ActionAddHost& action) = 0;

    virtual std::string getDelDomainQuery(const ActionDelDomain& action) = 0;

    virtual std::string getDelHostQuery(const ActionDelHost& action) = 0;

protected:
    SqlConfiguration _masterConfig;

    SqlConfiguration _slaveConfig;
};


#endif //PDNS_SLAVE_ABSTRACTSQL_H
