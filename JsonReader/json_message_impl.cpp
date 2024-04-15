#include <json_message_impl.h>
#include <json_nlohmann_adapter.h>

using namespace ProcessManager;

bool json_message_impl::parse(const std::string& data)
{
    return false;
}

std::string json_message_impl::get(const std::string& key)
{
    return std::string();
}