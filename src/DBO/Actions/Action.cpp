//
// Created by robin on 8/9/15.
//

#include "Action.h"

Action::Action()
{
}

Action::~Action()
{
}

const std::string &Action::getDomain() const
{
    return _domain;
}

void Action::setDomain(const std::string &domain)
{
    _domain = domain;
}

const std::string Action::getSqlQuery() const
{
    return "SET @domain_id=(SELECT get_domain_id(\"" + _domain + "\"));\n" + getSql();
}

const std::string Action::getDhcpConf() const
{
    return getDhcp();
}

const std::string Action::getDhcp() const
{
    return "";
}
