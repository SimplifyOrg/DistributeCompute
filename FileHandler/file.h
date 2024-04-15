#pragma once

#include <string>
#include <filesystem>

namespace ProcessManager
{
    class file
    {
    private:
        /* data */
    public:
        file(/* args */);
        ~file();

        std::string readFile(const std::filesystem::path & filePath);
    };

} // namespace ProcessManager
