//
// Created by robin on 8/9/15.
//

#include "ActionDelDomain.h"
#include "../../DataAccess/AbstractSql.h"

ActionDelDomain::ActionDelDomain()
{
}

const std::string ActionDelDomain::getSql(AbstractSql* sqlDb) const
{
    return sqlDb->getDelDomainQuery(*this);
}
