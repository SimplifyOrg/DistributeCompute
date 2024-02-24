#include "event.h"
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
        std::map<bsl::string, std::function<void(bsl::string, bsl::string)>> handlers;
    public:
        event_loop(/* args */);
        ~event_loop();
    };    
} // namespace ProcessManager
