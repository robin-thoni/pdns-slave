//
// Created by robin on 8/9/15.
//

#include "ActionAddHost.h"

ActionAddHost::ActionAddHost()
{
}

const std::string ActionAddHost::getSql() const
{
    return "";
}

const std::string &ActionAddHost::getHost() const
{
    return _host;
}

void ActionAddHost::setHost(const std::string &host)
{
    _host = host;
}
const std::string &ActionAddHost::getRecordValue() const
{
    return _recordValue;
}

void ActionAddHost::setRecordValue(const std::string &recordValue)
{
    _recordValue = recordValue;
}

const std::string &ActionAddHost::getRecordType() const
{
    return _recordType;
}

void ActionAddHost::setRecordType(const std::string &recordType)
{
    _recordType = recordType;
}

const std::string &ActionAddHost::getDhcpMac() const
{
    return _dhcpMac;
}

void ActionAddHost::setDhcpMac(const std::string &dhcpMac)
{
    _dhcpMac = dhcpMac;
}

const std::string &ActionAddHost::getReverseDomain() const
{
    return _reverseDomain;
}

void ActionAddHost::setReverseDomain(const std::string &reverseDomain)
{
    _reverseDomain = reverseDomain;
}

bool ActionAddHost::isReverseEnabled() const
{
    return _reverseEnabled;
}

void ActionAddHost::setReverseEnabled(bool reverseEnabled)
{
    _reverseEnabled = reverseEnabled;
}
