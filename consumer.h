#pragma once

#include <rmqa_producer.h>
#include "connection.h"

using namespace BloombergLP;

namespace ProcessManager
{
    class consumer
    {
    private:
        /* data */
        bsl::shared_ptr<rmqa::Consumer> m_consumer;
        bsl::shared_ptr<connection> m_connection;
    public:
        consumer(connection* pConnection);
        ~consumer();

        bool createConsumer();
    };
}
