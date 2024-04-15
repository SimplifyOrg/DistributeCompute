#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include "json.hpp"

using namespace nlohmann;

class json_nlohmann_adapter
{
private:
    /* data */
    std::unique_ptr<json> m_configObject;
public:
    json_nlohmann_adapter(/* args */);
    ~json_nlohmann_adapter();
    bool readConfigFile(const std::filesystem::path &configPath);
    bool readData(const std::string& data);
    std::string get(const std::string &key);
};
