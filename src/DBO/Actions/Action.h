//
// Created by robin on 8/9/15.
//

#ifndef PDNS_SLAVE_ACTION_H
#define PDNS_SLAVE_ACTION_H

# include <string>

class Action
{
public:
    Action();
    virtual ~Action();

    virtual const std::string getSql() const = 0;

    const std::string &getDomain() const;

    void setDomain(const std::string &domain);

private:
    std::string _domain;
};


#endif //PDNS_SLAVE_ACTION_H
