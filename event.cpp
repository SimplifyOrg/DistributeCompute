#include "event.h"

using namespace ProcessManager;

event::event(bsl::string key, bsl::string data, bool async) 
    : eventKey(key), eventData(data), isAsyncEvent(async)
{
}

event::~event()
{
}