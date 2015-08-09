//
// Created by robin on 8/9/15.
//

#include "ActionDelDomain.h"

ActionDelDomain::ActionDelDomain()
{
}

const std::string ActionDelDomain::getSql() const
{
    return "DELETE FROM records WHERE domain_id=@domain_id;\n"
            "DELETE FROM comments WHERE domain_id=@domain_id;\n"
            "DELETE FROM zones WHERE domain_id=@domain_id;\n"
            "DELETE FROM cryptokeys WHERE domain_id=@domain_id;\n"
            "DELETE FROM domainmetadata WHERE domain_id=@domain_id;\n"
            "DELETE FROM domains WHERE id=@domain_id;\n";
}
