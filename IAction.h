#pragma once

#include <bsl_string.h>

using namespace BloombergLP;

namespace ProcessManager
{
    class IAction
    {
    public:
        virtual void execute() = 0;
        virtual void setData(const bsl::string& data) = 0;
    };
} // namespace ProcessManager



