#ifndef RELATIONDEFS_H
#define RELATIONDEFS_H

#include "Relations/BidirectionalAssociationRelation.h"
#include "Relations/ExtensionPointRelation.h"
#include "Relations/UnidirectionalAssociationRelation.h"
#include "Relations/UsesRelation.h"

#include "Styled.h"

typedef Styled<
            UnidirectionalAssociationRelation > UnidirectionalAssociation;

typedef Styled<
            BidirectionalAssociationRelation > BidirectionalAssociation;

typedef Styled<
            ExtensionPointRelation > ExtensionPoint;

typedef Styled<
            UsesRelation > UsesAssociation;

#endif // RELATIONDEFS_H
