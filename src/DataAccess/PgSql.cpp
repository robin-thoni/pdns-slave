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
    auto soa = action.getSoaNs() + " " + action.getSoaMail() + " " + std::to_string(time(nullptr)) + " "
               + std::to_string(action.getSoaRefresh()) + " " + std::to_string(action.getSoaRetry()) + " "
               + std::to_string(action.getSoaExpire()) + " " + std::to_string(action.getSoaTtl());

    return "INSERT INTO domains (name, type) VALUES (\'" + action.getDomain() + "\', \'MASTER\');\n"
                   "INSERT INTO zones (domain_id, owner, zone_templ_id) VALUES "
                   "((SELECT id FROM domains WHERE name=\'" + action.getDomain() + "\'), "
                   "(SELECT id FROM users ORDER BY id LIMIT 1), 0);\n"
                   "INSERT INTO records (domain_id, name, type, content, ttl, prio, change_date)\n"
                   "    VALUES((SELECT id FROM domains WHERE name=\'" + action.getDomain() + "\'), \'"
           + action.getDomain() + "\', \'SOA\', \'" + soa + "\', " + std::to_string(action.getTtl()) + ", 0, "
           + std::to_string(time(nullptr)) + ");\n";
}

std::string PgSql::getAddHostQuery(const ActionAddHost &action)
{
    auto host = action.getHost().empty() ? action.getDomain() : action.getHost() + "." + action.getDomain();
    auto query = "INSERT INTO records (domain_id, name, type, content, ttl, prio, change_date)\n"
                 "    VALUES((SELECT id FROM domains WHERE name=\'" + action.getDomain() + "\'), \'"
                 + host + "\', \'" + action.getRecordType() + "\', \'"
                 + action.getRecordValue() + "\', " + std::to_string(action.getTtl())
                 + ", 0, " + std::to_string(time(nullptr)) + ");\n";

    if (action.isReverseEnabled() && action.getRecordType() == "A")
    {
        auto reversedValue = action.getReversedValue();
        auto reverseDomain = action.getReverseDomain().empty() ? "in-addr.arpa" :
                             action.getReverseDomain() + ".in-addr.arpa";

        query += "INSERT INTO records (domain_id, name, type, content, ttl, prio, change_date)\n"
                         "    VALUES((SELECT id FROM domains WHERE name=\'" + reverseDomain + "\'), \'"
                 + reversedValue + "." + reverseDomain + "\', \'PTR\', \'" + action.getHost()
                 + "." + action.getDomain() + "\', " + std::to_string(action.getTtl()) + ", 0, "
                 + std::to_string(time(nullptr)) + ");\n";
    }

    return query;
}

std::string PgSql::getDelDomainQuery(const ActionDelDomain &action)
{
    return "DELETE FROM records WHERE domain_id=(SELECT id FROM domains WHERE name=\'" + action.getDomain() + "\');\n"
           "DELETE FROM comments WHERE domain_id=(SELECT id FROM domains WHERE name=\'" + action.getDomain() + "\');\n"
           "DELETE FROM zones WHERE domain_id=(SELECT id FROM domains WHERE name=\'" + action.getDomain() + "\');\n"
           "DELETE FROM cryptokeys WHERE domain_id=(SELECT id FROM domains WHERE name=\'" + action.getDomain() + "\');\n"
           "DELETE FROM domainmetadata WHERE domain_id=(SELECT id FROM domains WHERE name=\'" + action.getDomain() + "\');\n"
           "DELETE FROM domains WHERE id=(SELECT id FROM domains WHERE name=\'" + action.getDomain() + "\');\n";
}

std::string PgSql::getDelHostQuery(const ActionDelHost &action)
{
    return "DELETE FROM records WHERE name=\'" + action.getHost() + "." + action.getDomain() + "\' AND "
            "domain_id=(SELECT id FROM domains WHERE name=\'" + action.getDomain() + "\');";
}
