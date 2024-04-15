#include <json_nlohmann_adapter.h>
#include <iostream>
#include <file.h>
// #include <string>

static bool validateKey(const std::string &key)
{
    if(key.empty())
    {
        std::cerr << "Empty key provided" << std::endl;
        return false;
    }
    return true;
}

json_nlohmann_adapter::json_nlohmann_adapter(/* args */)
{
}

json_nlohmann_adapter::~json_nlohmann_adapter()
{
    // m_configObject.release();
}

bool json_nlohmann_adapter::readConfigFile(const std::filesystem::path & configPath)
{
    try
    {
        ProcessManager::file configFile;
        std::string tempConf = configFile.readFile(configPath);
        if(readData(tempConf.c_str()))
        {
            return true;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }

    return true;
}

bool json_nlohmann_adapter::readData(const std::string& data)
{
    json* tempJson = new json(json::parse(data.c_str()));
    m_configObject.reset(tempJson);
    return true;
}

std::string json_nlohmann_adapter::get(const std::string &key)
{
    if(!validateKey(key))
    {
        return std::string();
    }

    if(!m_configObject->contains(key.c_str()))
    {
        std::cerr << "Key \"" << key <<"\" not present in the config" << std::endl;
        return std::string();
    }
    auto value = m_configObject->at(key);
    std::string val;
    value.get_to(val);
    return val;
}