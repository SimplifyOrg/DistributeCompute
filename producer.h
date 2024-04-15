#pragma once

#include <rmqt_result.h>
#include <rmqa_producer.h>
#include <connection.h>
#include <bsl_memory.h>
#include <functional>

using namespace BloombergLP;

namespace ProcessManager
{
    class producer
    {
    private:
        bsl::shared_ptr<rmqa::Producer> m_producer;
        std::shared_ptr<connection> m_connection;
        uint16_t m_maxOutstandingConfirms;
    public:
        producer(std::shared_ptr<connection> pConnection);
        ~producer();

        bool createProducer();
        void sendMessage(bsl::string & message, void(*brokerAckCallback)(const rmqt::Message& message,
                                                                    const bsl::string& routingKey,
                                                                    const rmqt::ConfirmResponse& response));
        void setMaxQueueSize(uint16_t count) { m_maxOutstandingConfirms = count; }
    };
};


