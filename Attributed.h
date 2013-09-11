#ifndef ATTRIBUTED_H
#define ATTRIBUTED_H

#include "IAttributable.h"

#include <map>

template <typename T>
class Attributed : public IAttributable, public T
{
public:
    void setAttribute(const std::string key, const std::string value)
    {
        std::map<std::string, std::string>::iterator it = mAttributeMap.find(key);

        if (mAttributeMap.end() == it) {
            mAttributeMap.insert(std::make_pair<std::string, std::string>(key, value));
        } else {
            it->second = value;
        }
    }

    const std::string getAttribute(const std::string& key) const
    {
        return mAttributeMap.at(key);
    }

    bool hasAttribute(const std::string& key)
    {
        return (mAttributeMap.end() != mAttributeMap.find(key));
    }

private:
    std::map<std::string, std::string> mAttributeMap;
};

#endif // ATTRIBUTED_H
