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
    if(configPath.empty() || std::filesystem::exists(configPath) == false)
    {
        std::cerr << "Config file path is not provided" << std::endl;
        return false;
    }
    else
    {
        std::cout << "Config file present at: " << configPath.c_str() << std::endl;
    }
    
    // read a JSON file
    std::ifstream configStream(configPath.c_str());
    std::string temp, tempConf;
    while(std::getline(configStream, temp)) {
        //Do with temp
        tempConf.append(temp);
    }
    json* tempJson = new json(json::parse(tempConf.c_str()));
    m_configObject.reset(tempJson);
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
        std::cerr << "Key \"" << key <<"\" not present in the config" << std::endl;
        return bsl::string();
    }
    auto value = m_configObject->at(key);
    return bsl::string(value.dump().c_str());
}