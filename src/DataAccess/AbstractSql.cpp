//
// Created by robin on 4/6/16.
//

#include "AbstractSql.h"

AbstractSql::~AbstractSql()
{
}

AbstractSql::AbstractSql(const SqlConfiguration &masterConfig, const SqlConfiguration &slaveConfig)
        : _masterConfig(masterConfig)
        , _slaveConfig(slaveConfig)
{
}
