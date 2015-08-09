//
// Created by robin on 8/9/15.
//

#include "ActionAddDomain.h"

ActionAddDomain::ActionAddDomain()
{
}

const std::string &ActionAddDomain::getSoaNs() const
{
    return _soaNs;
}

void ActionAddDomain::setSoaNs(const std::string &soaNs)
{
    _soaNs = soaNs;
}

const std::string &ActionAddDomain::getSoaMail() const
{
    return _soaMail;
}

void ActionAddDomain::setSoaMail(const std::string &soaMail)
{
    _soaMail = soaMail;
}

int ActionAddDomain::getSoaRefresh() const
{
    return _soaRefresh;
}

void ActionAddDomain::setSoaRefresh(int soaRefresh)
{
    _soaRefresh = soaRefresh;
}

int ActionAddDomain::getSoaRetry() const
{
    return _soaRetry;
}

void ActionAddDomain::setSoaRetry(int soaRetry)
{
    _soaRetry = soaRetry;
}

int ActionAddDomain::getSoaExpire() const
{
    return _soaExpire;
}

void ActionAddDomain::setSoaExpire(int soaExpire)
{
    _soaExpire = soaExpire;
}

int ActionAddDomain::getSoaTtl() const
{
    return _soaTtl;
}

void ActionAddDomain::setSoaTtl(int soaTtl)
{
    _soaTtl = soaTtl;
}

int ActionAddDomain::getTtl() const
{
    return _ttl;
}

void ActionAddDomain::setTtl(int ttl)
{
    _ttl = ttl;
}

const std::string ActionAddDomain::getSql() const //ns.rthoni.com rthoni.hotmail.fr 2015080600 28800 7200 604800 86400
{
    auto soa = _soaNs + " " + _soaMail + " " + std::to_string(time(nullptr)) + " " + std::to_string(_soaRefresh)
             + " " + std::to_string(_soaRetry)+ " " + std::to_string(_soaExpire) + " " + std::to_string(_soaTtl);

    return "INSERT INTO domains (name, type) VALUES (\"" + _domain + "\", \"MASTER\");\n"
            "SET @domain_id=(SELECT id FROM domains WHERE name=\"" + _domain + "\");\n"
            "INSERT INTO zones (domain_id, owner, zone_templ_id) VALUES (@domain_id, "
            "(SELECT id FROM users ORDER BY id LIMIT 1), 0);\n"
            "INSERT INTO records (domain_id, name, type, content, ttl, prio, change_date)\n"
            "    VALUES(@domain_id, \"" + _domain + "\", \"SOA\","
            " \"" + soa + "\", " + std::to_string(_ttl) + ", 0, " + std::to_string(time(nullptr)) + ");\n";
}
