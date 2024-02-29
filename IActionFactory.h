#pragma once

#include "IAction.h"

namespace ProcessManager
{
    class IActionFactory
    {
    public:
        virtual IAction& createAction() = 0;

    };
} // namespace ProcessManager
