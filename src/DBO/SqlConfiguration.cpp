//
// Created by robin on 8/8/15.
//

#include "SqlConfiguration.h"

SqlConfiguration::SqlConfiguration()
{
}
const std::string &SqlConfiguration::getHost() const
{
    return _host;
}

void SqlConfiguration::setHost(const std::string &host)
{
    _host = host;
}

const std::string &SqlConfiguration::getUser() const
{
    return _user;
}

void SqlConfiguration::setUser(const std::string &user)
{
    _user = user;
}

const std::string &SqlConfiguration::getPassword() const
{
    return _password;
}

void SqlConfiguration::setPassword(const std::string &password)
{
    _password = password;
}

const std::string &SqlConfiguration::getDatabase() const
{
    return _database;
}

void SqlConfiguration::setDatabase(const std::string &database)
{
    _database = database;
}
