#pragma once

#include <rmqt_message.h>
#include <rmqa_consumer.h>
#include <iostream>

using namespace BloombergLP;

namespace ProcessManager
{
    class MessageConsumer 
    {
    private:
        bool processMessage(const rmqt::Message& message);

    public:
        void operator()(rmqp::MessageGuard& messageGuard);
    };
}
