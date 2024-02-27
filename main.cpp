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
#include "event_loop.h"
#include <thread>

using namespace BloombergLP;
using namespace ProcessManager;

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "USAGE: " << argv[0] << " <config.json path> \n";
        return 1;
    }
    const std::filesystem::path path = argv[1];
    bsl::shared_ptr<config> conf = bsl::make_shared<config>();
    if(!conf->readConfigFile(path))
    {
        std::cerr << "Error reading conf file" << "\n";
        return -1;
        //return bsl::string("ERROR: Could not read configuration at: ") + path.generic_string();
    }
    bsl::shared_ptr<connection> conn = bsl::make_shared<connection>(conf);
    if(!conn->createConnection())
    {
        //return bsl::string("ERROR: Failed to connect");
        return -1;
    }
    bsl::shared_ptr<consumer> cons = bsl::make_shared<consumer>(conn);
    cons->createConsumer();
    event_loop& evLoop = event_loop::getInstance();

    try
    {
        // bsl::string uniqueEventKey = "message_" + bsl::to_string(eventId);
        // event ev(uniqueEventKey, path.generic_string(), false);
        // std::cout << "Currrent Thread id: " << std::this_thread::get_id() << std::endl;
        // evLoop
        //     .on(uniqueEventKey, [](const bsl::string& data){
        //         std::cout << "Currrent Thread id: " << std::this_thread::get_id() << std::endl;
        //         // bsl::shared_ptr<config> conf = bsl::make_shared<config>();
        //         // const std::filesystem::path path = data.c_str();
        //         // if(!conf->readConfigFile(path))
        //         // {
        //         //     std::cerr << "Error reading conf file" << "\n";
        //         //     // bsl::shared_ptr<connection> conn = bsl::make_shared<connection>(conf.get());
        //         //     // if(conn->createConnection())
        //         //     // {
        //         //     //     // Start operation
        //         //     //     if(conf->get("Mode") == "consumer")
        //         //     //     {
        //         //     //         bsl::shared_ptr<consumer> cons = bsl::make_shared<consumer>(conn.get());
        //         //     //         cons->createConsumer();
        //         //     //     }
        //         //     //     else
        //         //     //     {
        //         //     //         bsl::shared_ptr<producer> prod = bsl::make_shared<producer>(conn.get());
        //         //     //         if(prod->createProducer())
        //         //     //         {
        //         //     //             bsl::string msg = conf->get("Message");
        //         //     //             prod->sendMessage(msg, &receiveConfirmation);
        //         //     //         }
        //         //     //     }
        //         //     // }
        //         //     return bsl::string("ERROR: Could not read configuration at: ") + path.generic_string();
        //         // }
        //         // bsl::shared_ptr<connection> conn = bsl::make_shared<connection>(conf);
        //         // if(!conn->createConnection())
        //         // {
        //         //     return bsl::string("ERROR: Failed to connect");
        //         // }
        //         // bsl::shared_ptr<consumer> cons = bsl::make_shared<consumer>(conn);
        //         // cons->createConsumer();
        //         return bsl::string("Success");
        //     })
        //     .dispatch(ev);
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
