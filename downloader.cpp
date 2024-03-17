#include "downloader.h"
#include <cpr/cpr.h>

using namespace ProcessManager;

downloader::downloader(/* args */)
{
}

downloader::~downloader()
{
}

void downloader::download(bsl::string url, bsl::string processName)
{
    std::ofstream of(processName.c_str(), std::ios::binary);
    cpr::Response r = cpr::Download(of, cpr::Url{url.c_str()});
}