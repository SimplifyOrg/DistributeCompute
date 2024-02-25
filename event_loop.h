#include "event.h"
#include "event_result.h"
#include <deque>
#include <functional>
#include <map>

using namespace BloombergLP;

namespace ProcessManager
{    
    class event_loop
    {
    private:
        /* data */
        // TODO : Add framework for prioritising some events
        std::deque<event> events;
        std::map<bsl::string, std::function<bsl::string(bsl::string)>> handlers;
        std::deque<event_result> results;
    public:
        event_loop(/* args */);
        ~event_loop();

        event_loop& on(bsl::string key, std::function<bsl::string(bsl::string)>);

        void dispatch(event &ev);

        void run();

    private:
        void produceOutputFor(event_result &eventResult);
        void processSync(event &ev);
        void processAsync(event &ev);
    };    
} // namespace ProcessManager
