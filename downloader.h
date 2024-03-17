#pragma once

#include <bsl_string.h>

namespace ProcessManager
{
    class downloader
    {
    private:
        /* data */
    public:
        downloader(/* args */);
        ~downloader();

        void download(bsl::string url, bsl::string processName);
    };  
} // namespace ProcessManager

