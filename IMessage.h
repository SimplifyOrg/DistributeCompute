#pragma once

#include <string>

namespace ProcessManager
{
    /**
     * Public interface to handle message parsing and information exchange
     *
     * */

    class IMessage
    {
    public:
        /**
         * API to parse and store messages. Idea is to support
         * multiple message formats. Client need to inject the
         * right dependency depending on the format of the data.
         * Important thing to note is message needs to be in key-value
         * pair, as client code will try to retieve value based on
         * key later on.
         *
         * @param message as null terminated string.
         *
         * @return true if pasring succeeded
         *
         * */
        virtual bool parse(const std::string& data) = 0;

        /**
         * API to get value corresponding to the key form the data
         * stored at the time of parsing.
         *
         * @param key for which the value is required
         *
         * @return
         * empty string if key is not found
         * corresponding value if the key is found
         *
         * */
        virtual std::string get(const std::string &key) = 0;
    };

} // namespace ProcessManager