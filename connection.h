#pragma once

#include <rmqa_rabbitcontext.h>
#include <rmqa_vhost.h>
#include <rmqt_simpleendpoint.h>
#include <bsl_memory.h>
#include <memory>
#include <rmqt_plaincredentials.h>
#include <bsl_string.h>
#include "IMessage.h"

using namespace BloombergLP;

namespace ProcessManager
{
    class connection
    {
    private:
        /* data */
        std::unique_ptr<rmqa::RabbitContext> m_rabbitContext;
        bsl::shared_ptr<rmqt::SimpleEndpoint> m_amqpEndPoint;
        bsl::shared_ptr<rmqt::PlainCredentials> m_amqpCredentials;
        std::shared_ptr<IMessage> m_config;
        bsl::shared_ptr<rmqa::VHost> m_vhost;
    public:
        connection(std::shared_ptr<IMessage> pConfig);
        ~connection();

        bool createConnection();

        bsl::shared_ptr<rmqa::VHost> getVhost() { return m_vhost; }

        std::shared_ptr<IMessage> getConfig() { return m_config; }

    };
}
