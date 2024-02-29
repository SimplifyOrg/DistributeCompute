#include "consumer_callback.h"
#include "event_loop.h"
#include "uuid_generator.h"
#include <thread>
#include <bsl_string.h>
#include <string>
#include <boost/process/search_path.hpp>
#include "config.h"

using namespace BloombergLP;
using namespace ProcessManager;

bool MessageConsumer::processMessage(const rmqt::Message& message)
{
    // process Message here
    //std::cout << "Payload: " << message.payload() << std::endl;
    boost::uuids::uuid messageId = GenerateUUID();
    bsl::string processString = boost::uuids::to_string(messageId);
    bsl::string uniqueEventKey = "message_" + processString;
    event ev(uniqueEventKey, (char *)(message.payload()), true);
    std::cout << "Currrent Thread id: " << std::this_thread::get_id() << std::endl;
    event_loop& evLoop = event_loop::getInstance();
    evLoop
        .on(uniqueEventKey, [](const bsl::string& data){
            std::cout << "Currrent Thread id: " << std::this_thread::get_id() << std::endl;
            std::cout << "Test data: " << data << std::endl;
            bsl::shared_ptr<config> conf = bsl::make_shared<config>();
            if(conf->readData(data))
            {
                boost::process::filesystem::path process = boost::process::search_path(conf->get("Process").c_str());
            }
            
            return bsl::string("Success");
        })
        .dispatch(ev);
    return true;
}

void MessageConsumer::operator()(rmqp::MessageGuard& messageGuard)
{
    if (processMessage(messageGuard.message())) 
    {
        messageGuard.ack();
    }
    else 
    {
        messageGuard.nack();
        // Would automatically nack if it goes out of scope
    }
}