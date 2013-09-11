#ifndef RELATIONDEFS_H
#define RELATIONDEFS_H

#include "Relation.h"

#include "Identified.h"
#include "Coloured.h"
#include "Positioned.h"

typedef Identified<
            Positioned<
                Coloured<
                    Relation<UnidirectionalAssociationType> > > > UnidirectionalAssociation;

typedef Identified<
            Positioned<
                Coloured<
                    Relation<BidirectionalAssociationType> > > > BidirectionalAssociation;

typedef Identified<
            Positioned<
                Coloured<
                    Relation<ExtensionPointType> > > > ExtensionPoint;

typedef Identified<
            Positioned<
                Coloured<
                    Relation<UsesType> > > > UsesAssociation;

#endif // RELATIONDEFS_H
