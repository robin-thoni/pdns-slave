//
// Created by robin on 8/9/15.
//

#ifndef PDNS_SLAVE_ACTION_H
#define PDNS_SLAVE_ACTION_H

# include <string>
# include <memory>
# include <vector>

class Action
{
public:
    Action();
    virtual ~Action();

    const std::string getSqlQuery() const;

    const std::string &getDomain() const;

    void setDomain(const std::string &domain);

protected:
    virtual const std::string getSql() const = 0;

    std::string _domain;
};

typedef std::vector<std::shared_ptr<Action>> Actions;

#endif //PDNS_SLAVE_ACTION_H
