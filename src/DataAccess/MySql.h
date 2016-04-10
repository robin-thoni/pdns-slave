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


#endif //PDNS_SLAVE_MYSQL_H
