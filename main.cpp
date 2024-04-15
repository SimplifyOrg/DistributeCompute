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
#include <filesystem>

#include <memory>
#include <bsl_optional.h>
#include <bsl_vector.h>
#include "spdlog/spdlog.h"

#include <IMessage.h>
#include <json_message_impl.h>
#include <connection.h>
#include <consumer.h>
#include <producer.h>
#include <producer_callback.h>
#include <event_loop.h>
#include <thread>
#include <file.h>

using namespace BloombergLP;
using namespace ProcessManager;

int main(int argc, char** argv)
{
    if (argc < 2) {
        spdlog::critical("USAGE: {} <config.json path>", argv[0]);
        return 1;
    }
    const std::filesystem::path path = argv[1];
    std::shared_ptr<IMessage> conf = std::make_shared<ProcessManager::json_message_impl>();
    ProcessManager::file configFile;
    std::string tempConf = configFile.readFile(path);

    if(tempConf.empty() == true)
    {
        std::cerr << "Error reading conf file" << "\n";
        return -1;
        //return bsl::string("ERROR: Could not read configuration at: ") + path.generic_string();
    }
    conf->parse(tempConf);
    std::shared_ptr<connection> conn = std::make_shared<connection>(conf);
    if(!conn->createConnection())
    {
        //return bsl::string("ERROR: Failed to connect");
        return -1;
    }
    std::shared_ptr<consumer> cons = std::make_shared<consumer>(conn);
    cons->createConsumer();
    event_loop& evLoop = event_loop::getInstance();

    try
    {
        do
        {
            evLoop.run();

        } while (true);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception: main() " << e.what() << '\n';
    }


    return 0;
}
