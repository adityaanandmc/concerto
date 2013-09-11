#ifndef NODEDEFS_H
#define NODEDEFS_H

#include "Nodes/ActorGraphNode.h"
#include "Nodes/AltFlowGraphNode.h"
#include "Nodes/CircleGraphNode.h"
#include "Nodes/RectangleGraphNode.h"
#include "Nodes/SecFlowGraphNode.h"
#include "Nodes/SquareGraphNode.h"
#include "Nodes/SubFlowGraphNode.h"
#include "Nodes/TriangleGraphNode.h"
#include "Nodes/UsecaseGraphNode.h"

#include "Identified.h"
#include "Attributed.h"
#include "Positioned.h"
#include "Coloured.h"

typedef Identified<
            Attributed<
                Positioned<
                    Coloured<
                        UsecaseGraphNode > > > > UsecaseNode;

typedef Identified<
            Attributed<
                Positioned<
                    Coloured<
                        ActorGraphNode > > > > ActorNode;

typedef Identified<
            Attributed<
                Positioned<
                    Coloured<
                        SubFlowGraphNode > > > > SubFlowNode;

typedef Identified<
            Attributed<
                Positioned<
                    Coloured<
                        AltFlowGraphNode > > > > AltFlowNode;

typedef Identified<
            Attributed<
                Positioned<
                    Coloured<
                        SecFlowGraphNode > > > > SecFlowNode;

typedef Identified<
            Positioned<
                Coloured<
                    SquareGraphNode > > > SquareNode;

typedef Identified<
            Positioned<
                Coloured<
                    RectangleGraphNode > > > RectangleNode;

typedef Identified<
            Positioned<
                Coloured<
                    CircleGraphNode > > > CircleNode;

typedef Identified<
            Positioned<
                Coloured<
                    TriangleGraphNode > > > TriangleNode;

#endif // NODEDEFS_H
