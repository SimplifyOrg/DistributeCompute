#include "downloader.h"
#include <cpr/cpr.h>

using namespace ProcessManager;

downloader::downloader(/* args */)
{
}

downloader::~downloader()
{
}

void downloader::download(bsl::string url)
{
    cpr::Response r = cpr::Get(cpr::Url{url.c_str()},
                      cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
                      cpr::Parameters{{"anon", "true"}, {"key", "value"}});
    r.status_code;                  // 200
    r.header["content-type"];       // application/json; charset=utf-8
    r.text;
}