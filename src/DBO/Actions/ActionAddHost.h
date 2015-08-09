//
// Created by robin on 8/9/15.
//

#ifndef PDNS_SLAVE_ACTIONADDHOST_H
#define PDNS_SLAVE_ACTIONADDHOST_H

# include "DBO/Actions/Action.h"

class ActionAddHost : public Action
{
public:
    ActionAddHost();

    const std::string &getHost() const;

    void setHost(const std::string &host);

    const std::string &getRecordValue() const;

    void setRecordValue(const std::string &recordValue);

    const std::string &getRecordType() const;

    void setRecordType(const std::string &recordType);

    const std::string &getDhcpMac() const;

    void setDhcpMac(const std::string &dhcpMac);

    const std::string &getReverseDomain() const;

    void setReverseDomain(const std::string &reverseDomain);

    bool isReverseEnabled() const;

    void setReverseEnabled(bool reverseEnabled);

    int getTtl() const;

    void setTtl(int ttl);

protected:
    const std::string getSql() const override;

    const std::string getDhcp() const override;

private:
    const std::string getReversedValue() const;

    std::string _host;

    std::string _recordValue;

    std::string _recordType;

    std::string _dhcpMac;

    std::string _reverseDomain;

    bool _reverseEnabled;

    int _ttl;
};


#endif //PDNS_SLAVE_ACTIONADDHOST_H
