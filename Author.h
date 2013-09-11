#ifndef AUTHOR_H
#define AUTHOR_H

#include "IAuthor.h"

#include <string>

class Author : public IAuthor
{
public:
    const std::string& getName() const
    {
        return theName;
    }

    void setName(const std::string& theName)
    {
        this->theName = theName;
    }

protected:
    std::string theName;
};

#endif // AUTHOR_H
