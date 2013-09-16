#ifndef STDSTRINGUTIL_H
#define STDSTRINGUTIL_H

namespace Util {
    namespace StdString {

    #include <sstream>

    template <typename T>
    const T fromString(const std::string& str)
    {
        T ret;
        std::istringstream iss(str);
        iss >> ret;

        return ret;
    }

    template <typename T>
    const std::string toString(const T in)
    {
        std::ostringstream oss;
        oss << in;

        return oss.str();
    }

    }
}

#endif // STDSTRINGUTIL_H
