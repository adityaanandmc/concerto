#ifndef NODEFACTORY_H
#define NODEFACTORY_H

#include "NodeDefs.h"

class NodeFactory
{
public:
    static INode *makeNode(NodeType theType)
    {
        switch (theType) {
        case UsecaseType:
            return new UsecaseNode();

        case ActorType:
            return new ActorNode();

        case SubFlowType:
            return new SubFlowNode();

        case AltFlowType:
            return new AltFlowNode();

        case SecFlowType:
            return new SecFlowNode();

        case GeomCircleType:
            return new CircleNode();

        case GeomRectangleType:
            return new RectangleNode();

        case GeomSquareType:
            return new SquareNode();

        case GeomTriangleType:
            return new TriangleNode();
        }

        return NULL;
    }
};

#endif // NODEFACTORY_H
