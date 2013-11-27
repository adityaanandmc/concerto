#ifndef NODE_H
#define NODE_H

#include "INode.h"
#include <string>

class Node : public INode
{
public:
    virtual ~Node() {}

    bool canBeSentinel() const
    {
        switch (theType) {
        case UsecaseType:
        case ActorType:
        case GeomCircleType:
        case GeomRectangleType:
        case GeomSquareType:
        case GeomTriangleType:
            return true;

        case SubFlowType:
        case AltFlowType:
        case SecFlowType:
        default:
            return false;
        }

        return false; // pretty much useless, but suppresses annoying warnings #gcc
    }

    bool validatable() const
    {
        switch (theType) {
        case UsecaseType:
        case ActorType:
        case SubFlowType:
        case AltFlowType:
        case SecFlowType:
            return true;

        default:
            return false;
        }

        return false; // pretty much useless, but suppresses annoying warnings #gcc
    }

    static bool relatableWith(const NodeType thisType, const NodeType theOther)
    {
        switch (thisType) {
        case UsecaseType:
            switch (theOther) {
            case UsecaseType:
            case ActorType:
            case SubFlowType:
            case AltFlowType:
            case SecFlowType:
                return true;
            default:
                return false;
            }
            break;

        case ActorType:
        case AltFlowType:
        case SecFlowType:
        case SubFlowType:
            switch (theOther) {
            case UsecaseType:
                return true;

            default:
                return false;
            }
            break;

        case GeomCircleType:
        case GeomRectangleType:
        case GeomSquareType:
        case GeomTriangleType:
        default:
            return false;
        }

        return false; // pretty much useless, but suppresses annoying warnings #gcc #again
    }

    const NodeType& getType() const
    {
        return theType;
    }

    void setType(const NodeType theType)
    {
        this->theType = theType;
    }

protected:
    NodeType theType;\
};

#endif // NODE_H
