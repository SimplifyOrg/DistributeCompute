#include "connection.h"
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>

static boost::uuids::uuid GenerateUUID()
{
    boost::uuids::random_generator generator;
    boost::uuids::uuid uuid = generator();
    return uuid;
}

connection::connection(config* pConfig)
{
    m_config.reset(std::move(pConfig));
}

connection::~connection()
{
}

void connection::createConnection()
{
    
}