#pragma once

#include <rmqt_message.h>

using namespace BloombergLP;

namespace ProcessManager
{
    class MessageConsumer 
    {
    private:
        bool processMessage(const rmqt::Message& message)
        {
            // process Message here
            return true;
        }

    public:
        void operator()(rmqp::MessageGuard& messageGuard)
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
    };
}
