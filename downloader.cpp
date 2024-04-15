#include <downloader.h>
#include <cpr/cpr.h>

using namespace ProcessManager;

downloader::downloader(std::shared_ptr<IMessage> pConfig)
{
    m_config = pConfig;
}

downloader::~downloader()
{
}

boost::process::filesystem::path downloader::download(std::string url)
{
    // Download file to default location for now
    // TODO: Enhance to download at specified location
    //
    boost::process::filesystem::path process = std::getenv("HOME");
    process.append("/");
    process.append(m_config->get("Process").c_str());

    std::ofstream of(process.generic_string(), std::ios::binary);
    cpr::Response r = cpr::Download(of, cpr::Url{url.c_str()});

    return process;
}