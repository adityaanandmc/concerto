#ifndef RELATIONDEFS_H
#define RELATIONDEFS_H

#include "Relations/BidirectionalAssociationRelation.h"
#include "Relations/ExtensionPointRelation.h"
#include "Relations/UnidirectionalAssociationRelation.h"
#include "Relations/UsesRelation.h"

#include "Identified.h"
#include "Coloured.h"
#include "Positioned.h"

typedef Identified<
            Positioned<
                Coloured<
                    UnidirectionalAssociationRelation > > > UnidirectionalAssociation;

typedef Identified<
            Positioned<
                Coloured<
                    BidirectionalAssociationRelation > > > BidirectionalAssociation;

typedef Identified<
            Positioned<
                Coloured<
                    ExtensionPointRelation > > > ExtensionPoint;

typedef Identified<
            Positioned<
                Coloured<
                    UsesRelation > > > UsesAssociation;

#endif // RELATIONDEFS_H
