#ifndef BIDIRECTIONALASSOCIATIONRELATION_H
#define BIDIRECTIONALASSOCIATIONRELATION_H

#include "../Relation.h"

class BidirectionalAssociationRelation : public Relation
{
public:
    BidirectionalAssociationRelation()
    {
        theType = BidirectionalAssociationType;
    }
};

#endif // BIDIRECTIONALASSOCIATIONRELATION_H
