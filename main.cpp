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

using namespace BloombergLP;

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
        
    }
    
    return 0;
}
