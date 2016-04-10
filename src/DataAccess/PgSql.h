//
// Created by robin on 4/6/16.
//

#ifndef PDNS_SLAVE_PGSQL_H
#define PDNS_SLAVE_PGSQL_H

#include "AbstractSql.h"

class PgSql : public AbstractSql
{
public:
    PgSql(const SqlConfiguration& masterConfig, const SqlConfiguration& slaveConfig);
    ~PgSql();

    BResult dump();

    BResult insert();

    BResult override(const std::string& sql);

    virtual std::string getAddDomainQuery(const ActionAddDomain &action) override;

    virtual std::string getAddHostQuery(const ActionAddHost &action) override;

    virtual std::string getDelDomainQuery(const ActionDelDomain &action) override;

    virtual std::string getDelHostQuery(const ActionDelHost &action) override;


private:
    const std::string getTempFile();

    BResult insertSlave(const std::string& file);

    std::string _dumpFilePath;

    std::string _overrideFilePath;
};


#endif //PDNS_SLAVE_PGSQL_H
