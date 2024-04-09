#include "spdlog/spdlog.h"
#include "../event_loop.h"
#include "../uuid_generator.h"
#include <bsl_string.h>

using namespace ProcessManager;
using namespace BloombergLP;

void testAsyncEventLoop()
{
    boost::uuids::uuid messageId_async = GenerateUUID();
    bsl::string processString_async = boost::uuids::to_string(messageId_async);
    bsl::string uniqueEventKey_async = "message_" + processString_async;

    event ev(uniqueEventKey_async, "Test payload async", true);
    spdlog::info("Created async event object");

    event_loop& evLoop = event_loop::getInstance();
    spdlog::info("Retrieved event loop object");

    evLoop
        .on(uniqueEventKey_async, [](const bsl::string& inputData){
            
            spdlog::info("Printing from async event execution: {}", inputData.c_str());
            spdlog::info("Returning success");
            return bsl::string("Success");
        })
        .dispatch(ev);
    spdlog::info("Dispatched async event. Order of this message can change per execution.");
}

void testSyncEventLoop()
{
    boost::uuids::uuid messageId_sync = GenerateUUID();
    bsl::string processString_sync = boost::uuids::to_string(messageId_sync);
    bsl::string uniqueEventKey_sync = "message_" + processString_sync;

    event ev(uniqueEventKey_sync, "Test payload sync", false);
    spdlog::info("Created sync event object");

    event_loop& evLoop = event_loop::getInstance();
    spdlog::info("Retrieved event loop object");
    evLoop
        .on(uniqueEventKey_sync, [](const bsl::string& inputData){
            
            spdlog::info("Printing from sync event execution: {}", inputData.c_str());
            spdlog::info("Returning success");
            return bsl::string("Success");
        })
        .dispatch(ev);
    spdlog::info("Dispatched sync event.");
}

int main()
{
    try
    {
        testAsyncEventLoop();
        testSyncEventLoop();        
    }
    catch(const std::exception& e)
    {
        spdlog::critical("Exception raised: {}", e.what());
        return 1;
    }
    
    spdlog::info("Event loop test passed");
    return 0;
}