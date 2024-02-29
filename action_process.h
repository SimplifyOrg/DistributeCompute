#pragma once

#include "IAction.h"

namespace ProcessManager
{
    class action_process : public IAction
    {
    private:
        bsl::string m_data;
    public:
        virtual void execute();
        virtual void setData(const bsl::string& data);
    };
} // namespace ProcessManager
