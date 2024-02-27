#include "consumer.h"
#include "consumer_callback.h"
#include <bdlpcre_regex.h>

using namespace ProcessManager;

namespace BloombergLP {
namespace rmqt {
namespace {
const size_t MAX_EXCHANGE_NAME_LENGTH = 127;
}
}
}

static bool validateName(const bsl::string& exchangeName)
{
    bdlpcre::RegEx regex;
    bsl::string errMsg;
    size_t errOff;
    regex.prepare(&errMsg, &errOff, "^[a-zA-Z0-9-_.:]*$");
    return (exchangeName.size() <= rmqt::MAX_EXCHANGE_NAME_LENGTH) &&
           0 == regex.match(exchangeName.c_str(), exchangeName.length());
}

bool processMessage(const rmqt::Message& message)
{
    // process Message here
    std::cout << "Payload: " << message.payload() << std::endl;
    return true;
}

void onMessage(rmqp::MessageGuard& messageGuard)
{
    if (processMessage(messageGuard.message())) 
    {
        messageGuard.ack();
    }
    else 
    {
        messageGuard.nack();
        // Would automatically nack if it goes out of scope
    }
}

consumer::consumer(bsl::shared_ptr<connection> pConnection)
{
    m_connection = pConnection;
}

consumer::~consumer()
{
}

bool consumer::createConsumer()
{    
    auto config = m_connection->getConfig();
    if(!validateName(config->get("ExchangeName")))
    {
        std::cerr << "Invalid Exchange name: " << config->get("ExchangeName") << std::endl;
        return false;
    }
    rmqa::Topology topology;
    rmqt::QueueHandle q1    = topology.addPassiveQueue(config->get("QueueName"));
    rmqt::ExchangeHandle e1 = topology.addPassiveExchange(config->get("ExchangeName"));
    //topology.bind(e1, q1, config->get("RoutingKey"));
    
    auto vhost = m_connection->getVhost();
    rmqt::Result<rmqa::Consumer> consumerResult =
                                    vhost->createConsumer(
                                        topology,            // topology
                                        q1,                  // queue
                                        MessageConsumer(),   // Consumer callback invoked on each message
                                        "testConnection-consumer", // Consumer Label (shows in Management UI)
                                        20                  // prefetch count
                                    );
    
    if (!consumerResult) 
    {
        // An argument passed to the consumer was bad, retrying will have no effect
        std::cerr << "An argument passed to the consumer was bad, retrying will have no effect"<< std::endl;
        return false;
    }
    
    m_consumer = consumerResult.value();
    return true;
}