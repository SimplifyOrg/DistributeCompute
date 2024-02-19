#pragma once

#include <rmqa_rabbitcontext.h>
#include <rmqa_vhost.h>
#include <rmqt_simpleendpoint.h>
#include <bsl_memory.h>
#include <rmqt_plaincredentials.h>
#include <memory>
#include <string>
#include "config.h"

using namespace BloombergLP;

class connection
{
private:
    /* data */
    std::unique_ptr<rmqa::RabbitContext> m_rabbitContext;
    bsl::shared_ptr<rmqt::SimpleEndpoint> m_amqpEndPoint;
    bsl::shared_ptr<rmqt::PlainCredentials> m_amqpCredentials;
    std::shared_ptr<config> m_config;
public:
    connection(config* pConfig);
    ~connection();

    void createConnection();

};
