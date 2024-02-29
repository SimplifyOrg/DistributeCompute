#pragma once

#include "IAction.h"
#include <filesystem>

namespace ProcessManager
{
    class action_process : public IAction
    {
    private:
        std::filesystem::path m_localProcessPath;
        bsl::string m_commandLineParams;
        bsl::vector<bsl::string> m_response;
    public:
        virtual void execute();
        virtual bsl::vector<bsl::string> getResponse() { return m_response; }
        action_process(std::filesystem::path localPath, bsl::string cmdLine) : 
            m_localProcessPath(localPath),
            m_commandLineParams(cmdLine)
        {}
    };
} // namespace ProcessManager
