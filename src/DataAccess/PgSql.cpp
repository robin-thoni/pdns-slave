//
// Created by robin on 4/6/16.
//

#include <fstream>
#include <string.h>
#include <unistd.h>
#include "PgSql.h"

#define tmpTemplate "/tmp/pdns-slave.XXXXXX"

PgSql::PgSql(const SqlConfiguration &masterConfig, const SqlConfiguration &slaveConfig)
        : AbstractSql(masterConfig, slaveConfig)
{
}

PgSql::~PgSql()
{
    if (!_dumpFilePath.empty())
    {
        unlink(_dumpFilePath.c_str());
        _dumpFilePath = "";
    }
    if (!_overrideFilePath.empty())
    {
        unlink(_overrideFilePath.c_str());
        _overrideFilePath = "";
    }
}

BResult PgSql::dump()
{
    BResult res;
    _dumpFilePath = getTempFile();
    auto command = std::string("PGPASSWORD='" + _masterConfig.getPassword() + "' "
                               + "pg_dump -h '" + _masterConfig.getHost() + "' "
                               + "-U '" + _masterConfig.getUser() + "' "
                               + "-w -c -x -O '" + _masterConfig.getDatabase() + "' "
                               + "> '" + _dumpFilePath + "'");
    int status = system(command.c_str());
    if (status == 0)
        return res.ok(true);
    return res.error("pg_dump exited with code " + std::to_string(status));
}

const std::string PgSql::getTempFile()
{
    char tmp[sizeof(tmpTemplate)];
    strcpy(tmp, tmpTemplate);
    mkstemp(tmp);
    return std::string(tmp);
}

BResult PgSql::insert()
{
    return insertSlave(_dumpFilePath);
}

BResult PgSql::override(const std::string &sql)
{
    _overrideFilePath = getTempFile();
    std::ofstream file(_overrideFilePath);
    if (!file)
        return BResult().error("Could not open temp file " + _overrideFilePath);
    file << sql;
    file.close();
    return insertSlave(_overrideFilePath);
}

BResult PgSql::insertSlave(const std::string &file)
{
    BResult res;
    auto command = std::string("cat '" + file + "' | PGPASSWORD='" + _slaveConfig.getPassword() + "' "
                               + "psql -h '" + _slaveConfig.getHost() + "' "
                               + "-U '" + _slaveConfig.getUser() + "' "
                               + "-w -d '" + _slaveConfig.getDatabase() + "' > /dev/null");
    int status = system(command.c_str());
    if (status == 0)
        return res.ok(true);
    return res.error("psql exited with code " + std::to_string(status));
}

std::string PgSql::getAddDomainQuery(const ActionAddDomain &action)
{
    return "";
}

std::string PgSql::getAddHostQuery(const ActionAddHost &action)
{
    return "";
}

std::string PgSql::getDelDomainQuery(const ActionDelDomain &action)
{
    return "";
}

std::string PgSql::getDelHostQuery(const ActionDelHost &action)
{
    return "";
}
