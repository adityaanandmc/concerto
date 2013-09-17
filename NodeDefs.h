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
#include "Styled.h"
#include "Labelled.h"

typedef Identified<
            Attributed<
                Labelled<
                    Positioned<
                        Styled<
                            UsecaseGraphNode > > > > > UsecaseNode;

typedef Identified<
            Labelled<
                Positioned<
                    Styled<
                        ActorGraphNode > > > > ActorNode;

typedef Identified<
            Attributed<
                Labelled<
                    Positioned<
                        Styled<
                            SubFlowGraphNode > > > > > SubFlowNode;

typedef Identified<
            Attributed<
                Labelled<
                    Positioned<
                        Styled<
                            AltFlowGraphNode > > > > > AltFlowNode;

typedef Identified<
            Attributed<
                Labelled<
                    Positioned<
                        Styled<
                            SecFlowGraphNode > > > > > SecFlowNode;

typedef Identified<
            Labelled<
                Positioned<
                    Styled<
                        SquareGraphNode > > > > SquareNode;

typedef Identified<
            Labelled<
                Positioned<
                    Styled<
                        RectangleGraphNode > > > > RectangleNode;

typedef Identified<
            Labelled<
                Positioned<
                    Styled<
                        CircleGraphNode > > > > CircleNode;

typedef Identified<
            Labelled<
                Positioned<
                    Styled<
                        TriangleGraphNode > > > > TriangleNode;

#endif // NODEDEFS_H
