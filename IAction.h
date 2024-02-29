#pragma once

#include <bsl_string.h>
#include <bsl_vector.h>

using namespace BloombergLP;

namespace ProcessManager
{
    class IAction
    {
    public:
        virtual void execute() = 0;
        virtual bsl::vector<bsl::string> getResponse() = 0;
    };
} // namespace ProcessManager



