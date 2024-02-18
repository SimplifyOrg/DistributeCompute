#pragma once
#include <filesystem>
#include <memory>
#include <string>
#include "json.hpp"

using namespace nlohmann;

class config
{
private:
    /* data */
    std::unique_ptr<json> m_configObject;
public:
    config(/* args */);
    ~config();
    bool readConfigFile(std::filesystem::path & configPath);
    std::string get(std::string key);
};
