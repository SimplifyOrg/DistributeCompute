#include "downloader.h"
#include <cpr/cpr.h>

using namespace ProcessManager;

downloader::downloader(bsl::shared_ptr<config> pConfig)
{
    m_config = pConfig;
}

downloader::~downloader()
{
}

boost::process::filesystem::path downloader::download(bsl::string url, bsl::string processName)
{
    std::ofstream of(processName.c_str(), std::ios::binary);
    cpr::Response r = cpr::Download(of, cpr::Url{url.c_str()});

    boost::process::filesystem::path process = std::getenv("HOME");
    process.append("/");
    process.append(m_config->get("Process").c_str());

    return process;
}