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
    : AbstractSql(masterConfig, slaveConfig)
{
}

MySql::~MySql()
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

std::string MySql::getAddDomainQuery(const ActionAddDomain &action)
{
    auto soa = action.getSoaNs() + " " + action.getSoaMail() + " " + std::to_string(time(nullptr)) + " "
               + std::to_string(action.getSoaRefresh()) + " " + std::to_string(action.getSoaRetry()) + " "
               + std::to_string(action.getSoaExpire()) + " " + std::to_string(action.getSoaTtl());

    return "INSERT INTO domains (name, type) VALUES (\"" + action.getDomain() + "\", \"MASTER\");\n"
            "SET @domain_id=(SELECT id FROM domains WHERE name=\"" + action.getDomain() + "\");\n"
                   "INSERT INTO zones (domain_id, owner, zone_templ_id) VALUES (@domain_id, "
                   "(SELECT id FROM users ORDER BY id LIMIT 1), 0);\n"
                   "INSERT INTO records (domain_id, name, type, content, ttl, prio, change_date)\n"
                   "    VALUES(@domain_id, \"" + action.getDomain() + "\", \"SOA\","
                   " \"" + soa + "\", " + std::to_string(action.getTtl()) + ", 0, "
           + std::to_string(time(nullptr)) + ");\n";
}

std::string MySql::getAddHostQuery(const ActionAddHost &action)
{
    auto host = action.getHost().empty() ? action.getDomain() : action.getHost() + "." + action.getDomain();
    auto query = "SET @domain_id=(SELECT id FROM domains WHERE name=\"" + action.getDomain() + "\");\n"
                         "INSERT INTO records (domain_id, name, type, content, ttl, prio, change_date)\n"
                         "    VALUES(@domain_id, \"" + host + "\", \"" + action.getRecordType() + "\","
                         " \"" + action.getRecordValue() + "\", " + std::to_string(action.getTtl())
                 + ", 0, " + std::to_string(time(nullptr)) + ");\n";

    if (action.isReverseEnabled() && action.getRecordType() == "A")
    {
        auto reversedValue = action.getReversedValue();
        auto reverseDomain = action.getReverseDomain().empty() ? "in-addr.arpa" :
                             action.getReverseDomain() + ".in-addr.arpa";

        query += "INSERT INTO records (domain_id, name, type, content, ttl, prio, change_date)\n"
                         "    VALUES((SELECT id FROM domains WHERE name=\"" + reverseDomain + "\"), \""
                 + reversedValue + "." + reverseDomain + "\", \"PTR\","
                         " \"" + action.getHost() + "." + action.getDomain() + "\", 84600, 0, "
                 + std::to_string(time(nullptr)) + ");\n";
    }

    return query;
}

std::string MySql::getDelDomainQuery(const ActionDelDomain &action)
{
    return "SET @domain_id=(SELECT id FROM domains WHERE name=\"" + action.getDomain() + "\");\n"
            "DELETE FROM records WHERE domain_id=@domain_id;\n"
            "DELETE FROM comments WHERE domain_id=@domain_id;\n"
            "DELETE FROM zones WHERE domain_id=@domain_id;\n"
            "DELETE FROM cryptokeys WHERE domain_id=@domain_id;\n"
            "DELETE FROM domainmetadata WHERE domain_id=@domain_id;\n"
            "DELETE FROM domains WHERE id=@domain_id;\n";
}

std::string MySql::getDelHostQuery(const ActionDelHost &action)
{
    return "SET @domain_id=(SELECT id FROM domains WHERE name=\"" + action.getDomain() + "\");\n"
            "DELETE FROM records WHERE name=\"" + action.getHost() + "." + action.getDomain() + "\" AND "
            "domain_id=@domain_id;";
}
