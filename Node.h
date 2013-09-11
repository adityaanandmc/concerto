#ifndef NODE_H
#define NODE_H

#include "INode.h"
#include <string>

template <NodeType nodeType>
class Node : public INode
{
public:
    Node()
    {
        this->theType = nodeType;
    }

    bool canBeSentinel() const
    {
        switch (nodeType) {
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
            return false;
        }
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
