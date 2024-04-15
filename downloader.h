#pragma once

#include <bsl_string.h>
#include <boost/process/search_path.hpp>
#include <boost/filesystem.hpp>
#include <IMessage.h>
#include <memory>

namespace ProcessManager
{
    class downloader
    {
    private:
        /* data */
        std::shared_ptr<IMessage> m_config;
    public:
        downloader(std::shared_ptr<IMessage> pConfig);
        ~downloader();

        boost::process::filesystem::path download(std::string url);
    };
} // namespace ProcessManager

