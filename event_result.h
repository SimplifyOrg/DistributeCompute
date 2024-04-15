#include <bsl_string.h>
#include <IMessage.h>

using namespace BloombergLP;

namespace ProcessManager
{
    typedef struct EventResult
    {
        /* data */
        bsl::string result;
        bsl::string key;

    } event_result;
} // namespace ProcessManager
