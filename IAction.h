#pragma once

#include <string>
#include <vector>

namespace ProcessManager
{
    class IAction
    {
    public:
        virtual void execute() = 0;
        virtual std::vector<std::string> getResponse() = 0;
    };
} // namespace ProcessManager



