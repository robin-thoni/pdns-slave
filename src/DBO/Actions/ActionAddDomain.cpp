//
// Created by robin on 8/9/15.
//

#include "ActionAddDomain.h"
#include "../../DataAccess/AbstractSql.h"

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

const std::string ActionAddDomain::getSql(AbstractSql* sqlDb) const
{
    return sqlDb->getAddDomainQuery(*this);
}
