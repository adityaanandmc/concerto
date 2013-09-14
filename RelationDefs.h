#ifndef RELATIONDEFS_H
#define RELATIONDEFS_H

#include "Relations/BidirectionalAssociationRelation.h"
#include "Relations/ExtensionPointRelation.h"
#include "Relations/UnidirectionalAssociationRelation.h"
#include "Relations/UsesRelation.h"

#include "Identified.h"
#include "Styled.h"
#include "Positioned.h"

typedef Identified<
            Positioned<
                Styled<
                    UnidirectionalAssociationRelation > > > UnidirectionalAssociation;

typedef Identified<
            Positioned<
                Styled<
                    BidirectionalAssociationRelation > > > BidirectionalAssociation;

typedef Identified<
            Positioned<
                Styled<
                    ExtensionPointRelation > > > ExtensionPoint;

typedef Identified<
            Positioned<
                Styled<
                    UsesRelation > > > UsesAssociation;

#endif // RELATIONDEFS_H
