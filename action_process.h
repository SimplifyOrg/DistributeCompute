#pragma once

#include "IAction.h"
#include <filesystem>

namespace ProcessManager
{
    class action_process : public IAction
    {
    private:
        std::filesystem::path m_localProcessPath;
        std::string m_commandLineParams;
        std::vector<std::string> m_response;
    public:
        virtual void execute();
        virtual std::vector<std::string> getResponse() { return m_response; }
        action_process(std::filesystem::path localPath, std::string cmdLine) :
            m_localProcessPath(localPath),
            m_commandLineParams(cmdLine)
        {}
    };
} // namespace ProcessManager
