//
// Created by robin on 8/9/15.
//

#include "ActionAddDomain.h"

ActionAddDomain::ActionAddDomain()
{
}

const std::string ActionAddDomain::getSql() const
{
    return "INSERT INTO domains (name, type) VALUES (\"" + _domain + "\", \"MASTER\");\n"
            "INSERT INTO zones (domain_id, owner, zone_templ_id) VALUES ((SELECT id FROM domains WHERE name=\""
           + _domain + "\"), (SELECT id FROM users ORDER BY id LIMIT 1), 0);";
}
