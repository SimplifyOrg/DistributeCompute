#include "config.h"
#include <fstream>
#include <iostream>

static bool validateKey(const bsl::string &key)
{
    if(key.empty())
    {
        std::cerr << "Empty key provided" << std::endl;
        return false;
    }
    return true;
}

config::config(/* args */)
{
}

config::~config()
{
    m_configObject.release();
}

bool config::readConfigFile(const std::filesystem::path & configPath)
{
    if(configPath.empty())
    {
        std::cerr << "Config file path is not provided" << std::endl;
        return false;
    }
    
    // read a JSON file
    std::ifstream configStream(configPath.c_str());
    json tempConfigObject;
    configStream >> tempConfigObject;
    m_configObject.reset(std::move(&tempConfigObject));
    return true;
}

bsl::string config::get(const bsl::string &key)
{
    if(!validateKey(key))
    {
        return bsl::string();
    }

    if(!m_configObject->contains(key.c_str()))
    {
        std::cerr << "Key not present in the config" << std::endl;
        return bsl::string();
    }
    auto value = m_configObject->at(key);
    return bsl::string(value.dump().c_str());
}