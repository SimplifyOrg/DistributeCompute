#include "event_loop.h"
#include <thread>
#include <iostream>

using namespace ProcessManager;

event_loop* event_loop::m_instance = nullptr;
std::mutex event_loop::m_mutex;

event_loop::event_loop(/* args */)
{
}

event_loop::~event_loop()
{
}

event_loop& event_loop::on(bsl::string key, std::function<bsl::string(bsl::string)> handler)
{
    handlers[key] = handler;
    return *this;
}

void event_loop::dispatch(event &ev)
{
    events.emplace_back(ev);
}

void event_loop::run()
{
    if(events.empty() == false)
    {
        event ev = events.front(); events.pop_front();
        if(handlers.count(ev.eventKey) > 0)
        {
            if(ev.isAsyncEvent)
            {
                processAsync(ev);
            }
            else
            {
                processSync(ev);
            }
        }
    }

    if(results.empty() == false)
    {
        auto processedEvent = results.front(); results.pop_front();
        produceOutputFor(processedEvent);
    }
}

void event_loop::processAsync(event &ev) 
{
    std::thread([this, ev]() 
    {
        results.push_back({ev.eventKey, handlers[ev.eventKey](ev.eventData)});
    }).detach();
}

void event_loop::processSync(event &ev) 
{
    std::cout << ev.eventData << std::endl;
    results.push_back({ev.eventKey, handlers[ev.eventKey](ev.eventData)});
}

void event_loop::produceOutputFor(event_result &eventResult) 
{
    std::cout << "\nOutput for Event " << eventResult.key << " : " << eventResult.result << "\n";
}