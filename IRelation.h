#ifndef IRELATION_H
#define IRELATION_H

#include "RelationType.h"

struct IRelation
{
    virtual ~IRelation() {}

    virtual bool isBidirectional() const = 0;

    virtual const std::string& getTitle() const = 0;

    virtual void setTitle(const std::string& theTitle) = 0;

    virtual RelationType getType() const = 0;

    virtual void setType(const RelationType theType) = 0;
};

#endif // IRELATION_H
