//
// Created by robin on 8/9/15.
//

#ifndef PDNS_SLAVE_ACTIONADDDOMAIN_H
#define PDNS_SLAVE_ACTIONADDDOMAIN_H

# include "DBO/Actions/Action.h"

class ActionAddDomain : public Action
{
public:
    ActionAddDomain();

protected:
    const std::string getSql() const override;
};


#endif //PDNS_SLAVE_ACTIONADDDOMAIN_H
