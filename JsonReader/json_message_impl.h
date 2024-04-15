#pragma once
#include <IMessage.h>

namespace ProcessManager
{
    class json_message_impl : public IMessage
    {
    public:

        virtual bool parse(const std::string & data);
        virtual std::string get(const std::string& key);
    };

} // namespace ProcessManager
