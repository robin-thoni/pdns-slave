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

    virtual const std::string getSql() const = 0;

    const std::string &getDomain() const;

    void setDomain(const std::string &domain);

private:
    std::string _domain;
};

typedef std::vector<std::shared_ptr<Action>> Actions;

#endif //PDNS_SLAVE_ACTION_H
