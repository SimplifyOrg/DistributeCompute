#include <bsl_string.h>

using namespace BloombergLP;

namespace ProcessManager
{
    class event
    {
    public:
        /* data */
        bsl::string eventKey;
        bsl::string eventData;
        bool isAsyncEvent;
    public:
        event(bsl::string key, bsl::string data, bool async);
        ~event();
    };
}

