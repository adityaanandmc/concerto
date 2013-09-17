#ifndef ATTRIBUTED_H
#define ATTRIBUTED_H

#include "IAttributable.h"

#include <map>

template <typename T>
class Attributed : public IAttributable, public T
{
public:
    Attributed()
    {
        /* General */
        mAttributeMap.insert(std::make_pair<std::string, std::string>("Design Scope", ""));
        mAttributeMap.insert(std::make_pair<std::string, std::string>("Goal Level", ""));

        /* Pre-conditions */
        mAttributeMap.insert(std::make_pair<std::string, std::string>("Pre Conditions", ""));

        /* Post-conditions */
        mAttributeMap.insert(std::make_pair<std::string, std::string>("Minimal Guarantees", ""));
        mAttributeMap.insert(std::make_pair<std::string, std::string>("Success Guarantees", ""));
        mAttributeMap.insert(std::make_pair<std::string, std::string>("Trigger", ""));
        mAttributeMap.insert(std::make_pair<std::string, std::string>("Main Success Scenario", ""));

        /* Miscellaneous */
        mAttributeMap.insert(std::make_pair<std::string, std::string>("Notes", ""));
    }

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

    const std::map<std::string, std::string>& getPropertyList() const
    {
        return mAttributeMap;
    }

private:
    std::map<std::string, std::string> mAttributeMap;
};

#endif // ATTRIBUTED_H
