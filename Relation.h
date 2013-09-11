#ifndef RELATION_H
#define RELATION_H

#include "RelationType.h"

#include <string>

template <RelationType relationType>
class Relation : public IRelation
{
public:
    const bool isBidirectional() const
    {
        switch (theType) {
        case BidirectionalAssociationType:
            return true;

        default:
            return false;
        }
    }

    const std::string& getTitle() const
    {
        return theTitle;
    }

    void setTitle(const std::string& theTitle)
    {
        this->theTitle = theTitle;
    }

    const RelationType getType() const
    {
        return theType;
    }

    void setType(const RelationType theType)
    {
        this->theType = theType;
    }

protected:
    RelationType theType;

    std::string theTitle;
};

#endif // RELATION_H
