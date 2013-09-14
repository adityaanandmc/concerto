#ifndef RELATIONFACTORY_H
#define RELATIONFACTORY_H

#include "RelationDefs.h"

class RelationFactory
{
public:
    static IRelation *makeRelation(RelationType theType)
    {
        switch (theType) {
        case UnidirectionalAssociationType:
            return new UnidirectionalAssociation();

        case BidirectionalAssociationType:
            return new BidirectionalAssociation();

        case ExtensionPointType:
            return new ExtensionPoint();

        case UsesType:
            return new UsesAssociation();
        }

        return NULL;
    }
};

#endif // RELATIONFACTORY_H
