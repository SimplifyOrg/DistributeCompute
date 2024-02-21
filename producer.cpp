#include "producer.h"
#include <rmqa_topology.h>
#include <rmqa_producer.h>
#include "config.h"

ProcessManager::producer::producer(connection* pConnection)
{
    m_connection.reset(pConnection);
    m_maxOutstandingConfirms = 10;
}

ProcessManager::producer::~producer()
{
}

bool ProcessManager::producer::createProducer()
{
    auto config = m_connection->getConfig();
    
    // Create topology to be declared on every reconnection
    rmqa::Topology topology;
    rmqt::QueueHandle q1    = topology.addQueue(config->get("QueueName"));
    rmqt::ExchangeHandle e1 = topology.addExchange(config->get("ExchangeName"));
    
    auto vhost = m_connection->getVhost();

    try
    {
        auto producerResult = vhost->createProducer(topology, e1, m_maxOutstandingConfirms);
        if (!producerResult) 
        {
            // handle errors.
            std::cerr << "Error creating connection: " << producerResult.error();
            return false;
        }
        m_producer = producerResult.value();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    
    return true;
}
