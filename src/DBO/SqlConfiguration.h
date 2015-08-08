//
// Created by robin on 8/8/15.
//

#ifndef PDNS_SLAVE_SQLCONFIGURATION_H
#define PDNS_SLAVE_SQLCONFIGURATION_H

# include <string>

class SqlConfiguration
{
public:
    SqlConfiguration();
    const std::string &getHost() const;

    void setHost(const std::string &host);

    const std::string &getUser() const;

    void setUser(const std::string &user);

    const std::string &getPassword() const;

    void setPassword(const std::string &passwd);

    const std::string &getDatabase() const;

    void setDatabase(const std::string &database);

private:
    std::string _host;

    std::string _user;

    std::string _password;

    std::string _database;
};


#endif //PDNS_SLAVE_SQLCONFIGURATION_H
