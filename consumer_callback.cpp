#include "consumer_callback.h"
#include "event_loop.h"
#include "uuid_generator.h"
#include <thread>
#include <bsl_string.h>
#include <bsl_memory.h>
#include <string>
#include "spdlog/spdlog.h"
#include <boost/process/search_path.hpp>
#include <boost/filesystem.hpp>
#include "config.h"
#include "IAction.h"
#include "action_process.h"
#include "downloader.h"

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
        .on(uniqueEventKey, [](const bsl::string& inputData){
            std::cout << "Currrent Thread id: " << std::this_thread::get_id() << std::endl;
            std::cout << "Test data: " << inputData << std::endl;
            std::string data(inputData.c_str());
            if(data[data.size()-1] != '}')
            {
                auto pos = data.find_last_of('}');
                data.erase(data.begin()+pos+1, data.end());
            }
            bsl::shared_ptr<config> conf = bsl::make_shared<config>();
            bsl::vector<bsl::string> responseVec;
            if(conf->readData(data))
            {
                
                boost::process::filesystem::path process;
                if(conf->get("PathType") == "full-path")
                {
                    bsl::shared_ptr<config> confPath = bsl::make_shared<config>();
                    if(!confPath->readData(conf->get("downloadLocation")))
                    {
                        // Download to a default location in case
                        // download location is not provided or 
                        // improperly formatted
                        process.append("/home/");
                    }
                    
                    process.append(conf->get("Process").c_str());
                }
                else
                {
                    // Search in $PATH locations
                    process = boost::process::search_path(conf->get("Process").c_str());
                }
                
                if(boost::filesystem::exists(process))
                {
                    bsl::shared_ptr<IAction> action = bsl::make_shared<action_process>(process.generic_string(), conf->get("Param").c_str());
                    action->execute();
                    responseVec = action->getResponse();
                }
                else
                {
                    // If the file does not exit try downloading it
                    bsl::shared_ptr<downloader> downloadUtil = bsl::make_shared<downloader>();
                    try
                    {
                        downloadUtil->download(conf->get("DownloadURL").c_str(), conf->get("Process"));
                        bsl::shared_ptr<IAction> action = bsl::make_shared<action_process>(process.generic_string(), conf->get("Param").c_str());
                        action->execute();
                        responseVec = action->getResponse();
                    }
                    catch(const std::exception& e)
                    {
                        spdlog::critical("ERROR: Could not find the process file at: {}, Exception: {}", process.generic_string(), e.what());
                        return bsl::string("ERROR: Could not run process");
                    }
                }
            }
            else
            {
                return bsl::string("ERROR: Malformed data, need JSON format: ") + data;
            }

            if(responseVec.size() != 0)
            {
                bsl::string response;
                for(auto resp : responseVec)
                {
                    response.append(resp);
                }
                return response;
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