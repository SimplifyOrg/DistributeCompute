#pragma once

#include <bsl_string.h>
#include <boost/process/search_path.hpp>
#include <boost/filesystem.hpp>
#include "config.h"
#include <bsl_memory.h>

namespace ProcessManager
{
    class downloader
    {
    private:
        /* data */
        bsl::shared_ptr<config> m_config;
    public:
        downloader(bsl::shared_ptr<config> pConfig);
        ~downloader();

        boost::process::filesystem::path download(bsl::string url, bsl::string processName);
    };  
} // namespace ProcessManager

