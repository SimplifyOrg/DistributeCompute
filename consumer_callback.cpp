#include "consumer_callback.h"
#include "event_loop.h"
#include "uuid_generator.h"
#include <thread>
#include <bsl_string.h>
#include <string>

using namespace BloombergLP;
using namespace ProcessManager;

bool MessageConsumer::processMessage(const rmqt::Message& message)
{
    // process Message here
    //std::cout << "Payload: " << message.payload() << std::endl;
    boost::uuids::uuid messageId = GenerateUUID();
    bsl::string processString = boost::uuids::to_string(messageId);
    bsl::string uniqueEventKey = "message_" + processString;
    event ev(uniqueEventKey, (char *)(message.payload()), false);
    std::cout << "Currrent Thread id: " << std::this_thread::get_id() << std::endl;
    event_loop& evLoop = event_loop::getInstance();
    evLoop
        .on(uniqueEventKey, [](const bsl::string& data){
            std::cout << "Currrent Thread id: " << std::this_thread::get_id() << std::endl;
            std::cout << "Test data: " << data << std::endl;
            
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