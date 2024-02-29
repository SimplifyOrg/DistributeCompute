#include <boost/process.hpp>
#include <boost/process/io.hpp>
#include "action_process.h"
#include <string>
using namespace ProcessManager;

void action_process::execute()
{
    boost::process::ipstream is;
    boost::process::child c(m_localProcessPath.string(), std::string(m_commandLineParams.c_str()), boost::process::std_out > is);

    std::string line;
    while (c.running() && std::getline(is, line) && !line.empty())
    {
        m_response.push_back(line);
    }

    c.wait();
}