#pragma once

#include <rmqt_result.h>
#include <rmqp_producer.h>
#include "connection.h"
#include <bsl_memory.h>

using namespace BloombergLP;

namespace ProcessManager
{
    class producer
    {
    private:
        bsl::shared_ptr<rmqa::Producer> m_producer;
        bsl::shared_ptr<connection> m_connection;
        uint16_t m_maxOutstandingConfirms;
    public:
        producer(connection* pConnection);
        ~producer();

        bool createProducer();

        void setMaxQueueSize(uint16_t count) { m_maxOutstandingConfirms = count; }
    };
};


