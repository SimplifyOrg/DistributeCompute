#include "event_loop.h"
#include <thread>

using namespace ProcessManager;

event_loop::event_loop(/* args */)
{
}

event_loop::~event_loop()
{
}

event_loop& event_loop::on(bsl::string key, std::function<void(bsl::string, bsl::string)>)
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

    if(processedEvents.empty() == false)
    {
        auto processedEvent = processedEvents.front(); processedEvent.pop_front();
        produceOutputFor(processedEvent);
    }
}

void event_loop::processAsync(event &ev) 
{
    std::thread([this, ev]() 
    {
        processedEvents.push_back({ev.eventKey handlers[ev.eventKey](ev.eventData)});
    }).detach();
}

void event_loop::processSync(event &ev) 
{
    processedEvents.push_back({ev.eventKey, handlers[ev.eventKey](ev.eventData)});
}

void event_loop::produceOutputFor(event_result &eventResult) 
{
    std::cout << "\nOutput for Event " << eventResult.key << " : " << eventResult.result << "\n";
}