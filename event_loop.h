#include "event.h"
#include "event_result.h"
#include <deque>
#include <functional>
#include <map>
#include <mutex>

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
        static std::mutex m_mutex; // Mutex for thread safety.
        static event_loop* m_instance;
    public:

        static event_loop& getInstance() 
        {
            if (!m_instance) 
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                if (!m_instance) 
                {
                    m_instance = new event_loop();
                }
            }
            return *m_instance;
        }

        event_loop& on(bsl::string key, std::function<bsl::string(bsl::string)>);

        void dispatch(event &ev);

        void run();

    private:
        event_loop(/* args */);
        ~event_loop();
        event_loop(const event_loop&) = delete; // Delete copy constructor.
        event_loop& operator=(const event_loop&) = delete; // Delete assignment operator.
        void produceOutputFor(event_result &eventResult);
        void processSync(event &ev);
        void processAsync(event &ev);
    };    
} // namespace ProcessManager
