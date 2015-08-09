//
// Created by robin on 8/9/15.
//

#include "ActionDelHost.h"

ActionDelHost::ActionDelHost()
{
}

const std::string ActionDelHost::getSql() const
{
    return "DELETE FROM records WHERE name=\"" + _host + "." + _domain + "\" AND "
           "domain_id=@domain_id;";
}

const std::string &ActionDelHost::getHost() const
{
    return _host;
}

void ActionDelHost::setHost(const std::string &host)
{
    _host = host;
}
