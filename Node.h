#ifndef NODE_H
#define NODE_H

#include "INode.h"
#include <string>

class Node : public INode
{
public:
    Node()
    {
        this->theType = UndefinedNodeType;
    }

    virtual ~Node() {}

    bool canBeSentinel() const
    {
        switch (theType) {
        case UndefinedNodeType:
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

    const std::string getName() const
    {
        return theName;
    }

    void setName(const std::string& theName)
    {
        this->theName = theName;
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
    NodeType theType;

    std::string theName;
};

#endif // NODE_H
