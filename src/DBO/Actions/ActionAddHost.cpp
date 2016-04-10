//
// Created by robin on 8/9/15.
//
#include <string>
#include <sstream>
#include <vector>
#include "ActionAddHost.h"
#include "../../DataAccess/AbstractSql.h"

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

ActionAddHost::ActionAddHost()
{
}

const std::string ActionAddHost::getSql(AbstractSql* sqlDb) const
{
    return sqlDb->getAddHostQuery(*this);
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

int ActionAddHost::getTtl() const
{
    return _ttl;
}

void ActionAddHost::setTtl(int ttl)
{
    _ttl = ttl;
}

const std::string ActionAddHost::getReversedValue() const
{
    auto splitValue = split(_recordValue, '.');
    int index = 1;

    for (; index < splitValue.size(); ++index)
    {
        std::string reversedValue;
        for (int i = (int) splitValue.size() - 1 - index; i >= 0; --i)
            reversedValue += splitValue[i] + (i == 0 ? "" : ".");
        if (_reverseDomain == reversedValue)
            break;
    }
    std::string reversedValue;
    for (int i = (int) splitValue.size() - 1; i >= (int) splitValue.size() - index; --i)
        reversedValue += std::string(splitValue[i]) + (i == (int) splitValue.size() - index ? "" : ".");
    return reversedValue;
}

const std::string ActionAddHost::getDhcp() const
{
    if (!_dhcpMac.empty() && _recordType == "A")
    {
        return "\thost " + _host + " {\n"
                "\t\thardware ethernet " + _dhcpMac + ";\n"
                "\t\tfixed-address " + _host + "." + _domain + ";\n"
                "\t}\n";
    }
    else
        return "";
}