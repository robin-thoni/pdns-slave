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

private:
    const std::string getTempFile();

    BResult insertSlave(const std::string& file);

    std::string _dumpFilePath;

    std::string _overrideFilePath;
};


#endif //PDNS_SLAVE_PGSQL_H
