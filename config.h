#pragma once

#include <filesystem>
#include <memory>
#include <bsl_string.h>
#include "json.hpp"

using namespace nlohmann;
using namespace BloombergLP;

class config
{
private:
    /* data */
    std::unique_ptr<json> m_configObject;
public:
    config(/* args */);
    ~config();
    bool readConfigFile(const std::filesystem::path &configPath);
    bool readData(const bsl::string& data);
    bsl::string get(const bsl::string &key);
};
