#include "producer.h"
#include <rmqa_topology.h>
#include <rmqa_producer.h>
#include "config.h"

ProcessManager::producer::producer(bsl::shared_ptr<connection> pConnection)
{
    m_connection = pConnection;
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
            std::cerr << "Error creating connection: " << producerResult.error() << std::endl;
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

void ProcessManager::producer::sendMessage(bsl::string & message, 
                                        void(*brokerAckCallback)(const rmqt::Message& message, 
                                                                const bsl::string& routingKey, 
                                                                const rmqt::ConfirmResponse& response))
{
    auto config = m_connection->getConfig();
    bsl::string key = config->get("RoutingKey");
    if(key.empty())
    {
        std::cerr << "Routing key not found" << '\n';
    }
    
    if(!message.empty())
    {
        rmqt::Message messageToSend(
                    bsl::make_shared<bsl::vector<uint8_t> >(message.cbegin(), message.cend()));
        const rmqp::Producer::SendStatus sendResult =
            m_producer->send(messageToSend, config->get("RoutingKey"), brokerAckCallback);

        if (sendResult != rmqp::Producer::SENDING) {
            // Unable to enqueue this send
            std::cerr << "Unable to enqueue this message: " << message << '\n';
            return;
        }
    }
    else
    {
        std::cerr << "Aborted sending empty message." << '\n';
    }
}
