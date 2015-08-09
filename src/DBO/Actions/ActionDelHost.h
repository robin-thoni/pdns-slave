//
// Created by robin on 8/9/15.
//

#ifndef PDNS_SLAVE_ACTIONDELHOST_H
#define PDNS_SLAVE_ACTIONDELHOST_H

# include "DBO/Actions/Action.h"

class ActionDelHost : public Action
{
public:
    ActionDelHost();

    const std::string &getHost() const;

    void setHost(const std::string &host);

protected:
    const std::string getSql() const override;

private:
    std::string _host;
};


#endif //PDNS_SLAVE_ACTIONDELHOST_H
