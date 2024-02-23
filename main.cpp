#include <iostream>
#include <rmqa_connectionstring.h>
#include <rmqa_producer.h>
#include <rmqa_rabbitcontext.h>
#include <rmqa_topology.h>
#include <rmqa_vhost.h>
#include <rmqp_producer.h>
#include <rmqt_confirmresponse.h>
#include <rmqt_exchange.h>
#include <rmqt_message.h>
#include <rmqt_result.h>
#include <rmqt_vhostinfo.h>

#include <bsl_memory.h>
#include <bsl_optional.h>
#include <bsl_vector.h>

#include "config.h"
#include "connection.h"
#include "consumer.h"
#include "producer.h"
#include "producer_callback.h"

using namespace BloombergLP;
using namespace ProcessManager;

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "USAGE: " << argv[0] << " <config.json path> \n";
        return 1;
    }

    bsl::shared_ptr<config> conf = bsl::make_shared<config>();
    const std::filesystem::path path = argv[1];
    if(conf->readConfigFile(path))
    {
        bsl::shared_ptr<connection> conn = bsl::make_shared<connection>(conf.get());
        if(conn->createConnection())
        {
            // Start operation
            if(conf->get("Mode") == "consumer")
            {
                bsl::shared_ptr<consumer> cons = bsl::make_shared<consumer>(conn.get());
                cons->createConsumer();
            }
            else
            {
                bsl::shared_ptr<producer> prod = bsl::make_shared<producer>(conn.get());
                if(prod->createProducer())
                {
                    bsl::string msg = conf->get("Message");
                    prod->sendMessage(msg, &receiveConfirmation);
                }
            }
        }
    }
    else
    {
        std::cerr << "Error reading conf file" << "\n";
    }
    
    return 0;
}
