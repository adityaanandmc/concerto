#ifndef NODEDEFS_H
#define NODEDEFS_H

#include "Node.h"

#include "Identified.h"
#include "Attributed.h"
#include "Positioned.h"
#include "Coloured.h"

typedef Identified<
            Attributed<
                Positioned<
                    Coloured<
                        Node<UsecaseType> > > > > UsecaseNode;

typedef Identified<
            Attributed<
                Positioned<
                    Coloured<
                        Node<ActorType> > > > > ActorNode;

typedef Identified<
            Attributed<
                Positioned<
                    Coloured<
                        Node<SubFlowType> > > > > SubFlowNode;

typedef Identified<
            Attributed<
                Positioned<
                    Coloured<
                        Node<AltFlowType> > > > > AltFlowNode;

typedef Identified<
            Attributed<
                Positioned<
                    Coloured<
                        Node<SecFlowType> > > > > SecFlowNode;

typedef Identified<
            Positioned<
                Coloured<
                    Node<GeomSquareType> > > > SquareNode;

typedef Identified<
            Positioned<
                Coloured<
                    Node<GeomRectangleType> > > > RectangleNode;

typedef Identified<
            Positioned<
                Coloured<
                    Node<GeomCircleType> > > > CircleNode;

typedef Identified<
            Positioned<
                Coloured<
                    Node<GeomTriangleType> > > > TriangleNode;

#endif // NODEDEFS_H
