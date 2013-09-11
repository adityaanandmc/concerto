#ifndef IAUTHOR_H
#define IAUTHOR_H

struct IAuthor
{
    virtual ~IAuthor() {}

    virtual const std::string& getName() const = 0;

    virtual void setName(const std::string& theName) = 0;
};

#endif // IAUTHOR_H
