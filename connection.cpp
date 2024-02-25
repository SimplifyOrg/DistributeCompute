#include "connection.h"
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>

using namespace ProcessManager;

static boost::uuids::uuid GenerateUUID()
{
    boost::uuids::random_generator generator;
    boost::uuids::uuid uuid = generator();
    return uuid;
}

connection::connection(config* pConfig)
{
    m_config.reset(pConfig);
    m_rabbitContext = std::make_unique<rmqa::RabbitContext>();
    uint16_t port = std::atoi(m_config->get("Port").c_str());
    m_amqpEndPoint = bsl::make_shared<rmqt::SimpleEndpoint>(m_config->get("Host"), 
                                                            "rmqcpp",
                                                            port);
    m_amqpCredentials = bsl::make_shared<rmqt::PlainCredentials>(m_config->get("User"), 
                                                                m_config->get("Password"));
}

connection::~connection()
{
    m_vhost->close();
}

bool connection::createConnection()
{
    boost::uuids::uuid connectionName = GenerateUUID();
    bsl::string connectionString = boost::uuids::to_string(connectionName);
    
    try
    {
        m_vhost = m_rabbitContext->createVHostConnection(connectionString,
                                                        m_amqpEndPoint,
                                                        m_amqpCredentials); // returns immediately
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;
}