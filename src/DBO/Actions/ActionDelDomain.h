//
// Created by robin on 8/9/15.
//

#ifndef PDNS_SLAVE_ACTIONDELDOMAIN_H
#define PDNS_SLAVE_ACTIONDELDOMAIN_H

# include "DBO/Actions/Action.h"

class ActionDelDomain : public Action
{
public:
    ActionDelDomain();

protected:
    const std::string getSql(AbstractSql* sqlDb) const override;
};


#endif //PDNS_SLAVE_ACTIONDELDOMAIN_H
