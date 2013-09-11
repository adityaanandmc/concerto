#ifndef NODETYPE_H
#define NODETYPE_H

typedef enum __NodeType
{
    UndefinedNodeType = 0x02,

    UsecaseType = 0x55,
    ActorType,
    SubFlowType,
    AltFlowType,
    SecFlowType,

    GeomSquareType = 0x344,
    GeomRectangleType,
    GeomCircleType,
    GeomTriangleType
} NodeType;

#endif // NODETYPE_H
