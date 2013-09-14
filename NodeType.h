#ifndef NODETYPE_H
#define NODETYPE_H

typedef enum __NodeType
{
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
