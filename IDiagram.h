#ifndef IDIAGRAM_H
#define IDIAGRAM_H

#include <string>

#include "IAuthor.h"

struct IDiagram
{
    virtual ~IDiagram() {}

    virtual const std::string& getTitle() const = 0;

    virtual void setTitle(const std::string& theTitle) = 0;

    virtual const std::string& getDescription() const = 0;

    virtual void setDescription(const std::string& theDescription) = 0;

    virtual const IAuthor *getAuthor() const = 0;

    virtual IAuthor *grabAuthor() const = 0;

    virtual void setAuthor(const IAuthor *theAuthor) = 0;
};

#endif // IDIAGRAM_H
