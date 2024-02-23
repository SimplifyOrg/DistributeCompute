#pragma once

#include <rmqt_result.h>
#include <rmqa_producer.h>

using namespace BloombergLP;

namespace ProcessManager
{
    void receiveConfirmation(const rmqt::Message& message,
                            const bsl::string& routingKey,
                            const rmqt::ConfirmResponse& response)
    {
        if (response.status() == rmqt::ConfirmResponse::ACK) 
        {
            std::cout << "Message received by broker: " << message << std::endl;
        }
        else
        {
            // REJECT / RETURN indicate problem with the send request (bad routing
            // key?)
            std::cerr << "Message cannot be routed properly. Maybe the routing key \"" << routingKey << "\" is bad" << std::endl;
        }
    }
}