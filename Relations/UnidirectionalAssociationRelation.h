#ifndef UNIDIRECTIONALASSOCIATIONRELATION_H
#define UNIDIRECTIONALASSOCIATIONRELATION_H

#include "../Relation.h"

class UnidirectionalAssociationRelation : public Relation
{
public:
    UnidirectionalAssociationRelation()
    {
        theType = UnidirectionalAssociationType;
    }
};

#endif // UNIDIRECTIONALASSOCIATIONRELATION_H
