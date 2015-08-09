//
// Created by robin on 8/9/15.
//

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fstream>
#include "MySql.h"

#define tmpTemplate "/tmp/pdns-slave.XXXXXX"

MySql::MySql(const SqlConfiguration &masterConfig, const SqlConfiguration &slaveConfig)
    : _masterConfig(masterConfig)
    , _slaveConfig(slaveConfig)
{
}

MySql::~MySql()
{
    clean();
}

BResult MySql::dump()
{
    BResult res;
    _dumpFilePath = getTempFile();
    int status = system(std::string("mysqldump '-h" + _masterConfig.getHost() + "'"
                       + " '-u" + _masterConfig.getUser() + "'"
                       + " '-p" + _masterConfig.getPassword() + "'"
                       + " " + _masterConfig.getDatabase()
                       + " > " + _dumpFilePath).c_str());
    if (status == 0)
        return res.ok(true);
    return res.error("mysqldump exited with code " + std::to_string(status));
}

const std::string MySql::getTempFile()
{
    char tmp[sizeof(tmpTemplate)];
    strcpy(tmp, tmpTemplate);
    mkstemp(tmp);
    return std::string(tmp);
}

void MySql::clean()
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

BResult MySql::insert()
{
    return insertSlave(_dumpFilePath);
}

BResult MySql::override(const std::string &sql)
{
    _overrideFilePath = getTempFile();
    std::ofstream file(_overrideFilePath);
    if (!file)
        return BResult().error("Could not open temp file " + _overrideFilePath);
    file << sql;
    file.close();
    return insertSlave(_overrideFilePath);
}

BResult MySql::insertSlave(const std::string &file)
{
    BResult res;
    int status = system(std::string("cat " + file + " | mysql '-h" + _slaveConfig.getHost() + "'"
                                    + " '-u" + _slaveConfig.getUser() + "'"
                                    + " '-p" + _slaveConfig.getPassword() + "'"
                                    + " " + _slaveConfig.getDatabase()).c_str());
    if (status == 0)
        return res.ok(true);
    return res.error("mysql exited with code " + std::to_string(status));
}
