//
// Created by robin on 8/9/15.
//
#include <string>
#include <sstream>
#include <vector>
#include "ActionAddHost.h"

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

const std::string ActionAddHost::getSql() const
{
    auto host = _host.empty() ? _domain : _host + "." + _domain;
    auto query = "INSERT INTO records (domain_id, name, type, content, ttl, prio, change_date)\n"
            "    VALUES(@domain_id, \"" + host + "\", \"" + _recordType + "\","
            " \"" + _recordValue + "\", 84600, 0, " + std::to_string(time(nullptr)) + ");\n";

    if (_reverseEnabled && _recordType == "A")
    {
        auto reversedValue = getReversedValue();
        auto reverseDomain = _reverseDomain.empty() ? "in-addr.arpa" : _reverseDomain + ".in-addr.arpa";

        query += "INSERT INTO records (domain_id, name, type, content, ttl, prio, change_date)\n"
                 "    VALUES((SELECT id FROM domains WHERE name=\"" + reverseDomain + "\"), \""
                 + reversedValue + "." + reverseDomain + "\", \"PTR\","
                 " \"" + _host + "." + _domain + "\", 84600, 0, " + std::to_string(time(nullptr)) + ");\n";
    }

    return query;
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