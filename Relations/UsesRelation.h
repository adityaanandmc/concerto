#ifndef USESRELATION_H
#define USESRELATION_H

#include "../Relation.h"

class UsesRelation : public Relation
{
public:
    UsesRelation()
    {
        theType = UsesType;
    }
};

#endif // USESRELATION_H
