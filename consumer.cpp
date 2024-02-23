#include "consumer.h"
#include "consumer_callback.h"

ProcessManager::consumer::consumer(connection* pConnection)
{
    m_connection.reset(pConnection);
}

ProcessManager::consumer::~consumer()
{
}

bool ProcessManager::consumer::createConsumer()
{
    auto config = m_connection->getConfig();
    rmqa::Topology topology;
    rmqt::QueueHandle q1    = topology.addPassiveQueue(config->get("QueueName"));
    rmqt::ExchangeHandle e1 = topology.addPassiveExchange(config->get("ExchangeName"));
    
    auto vhost = m_connection->getVhost();
    rmqt::Result<rmqa::Consumer> consumerResult =
                                    vhost->createConsumer(
                                        topology,            // topology
                                        q1,                  // queue
                                        ProcessManager::MessageConsumer(),   // Consumer callback invoked on each message
                                        "my consumer label", // Consumer Label (shows in Management UI)
                                        500                  // prefetch count
                                    );

    if (!consumerResult) 
    {
        // An argument passed to the consumer was bad, retrying will have no effect
        std::cerr << "An argument passed to the consumer was bad, retrying will have no effect"<< std::endl;
        return;
    }
    m_consumer = consumerResult.value();
}