//
// Created by robin on 8/9/15.
//

#include "ActionDelHost.h"
#include "../../DataAccess/AbstractSql.h"

ActionDelHost::ActionDelHost()
{
}

const std::string ActionDelHost::getSql(AbstractSql* sqlDb) const
{
    return sqlDb->getDelHostQuery(*this);
}

const std::string &ActionDelHost::getHost() const
{
    return _host;
}

void ActionDelHost::setHost(const std::string &host)
{
    _host = host;
}
