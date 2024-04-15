#include <file.h>
#include <fstream>
#include <iostream>

using namespace ProcessManager;

file::file(/* args */)
{
}

file::~file()
{
}

std::string file::readFile(const std::filesystem::path & filePath)
{
    if(filePath.empty() || std::filesystem::exists(filePath) == false)
    {
        std::cerr << "Config file path is not provided" << std::endl;
        return std::string();
    }
    else
    {
        std::cout << "Config file present at: " << filePath.c_str() << std::endl;
    }

    // read a JSON file
    std::ifstream fileStream(filePath.c_str());
    std::string temp, tempConf;
    while(std::getline(fileStream, temp)) {
        //Do with temp
        tempConf.append(temp);
    }

    return tempConf;
}