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
            Attributed<
                Labelled<
                    Positioned<
                        Styled<
                            UsecaseGraphNode > > > > > ActorNode;

typedef Identified<
            Attributed<
                Labelled<
                    Positioned<
                        Styled<
                            UsecaseGraphNode > > > > > SubFlowNode;

typedef Identified<
            Attributed<
                Labelled<
                    Positioned<
                        Styled<
                            UsecaseGraphNode > > > > > AltFlowNode;

typedef Identified<
            Attributed<
                Labelled<
                    Positioned<
                        Styled<
                            UsecaseGraphNode > > > > > SecFlowNode;

typedef Identified<
            Labelled<
                Positioned<
                    Styled<
                        SquareGraphNode > > > > SquareNode;

typedef Identified<
            Labelled<
                Positioned<
                    Styled<
                        SquareGraphNode > > > > RectangleNode;

typedef Identified<
            Labelled<
                Positioned<
                    Styled<
                        SquareGraphNode > > > > CircleNode;

typedef Identified<
            Labelled<
                Positioned<
                    Styled<
                        SquareGraphNode > > > > TriangleNode;

#endif // NODEDEFS_H
