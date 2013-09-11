#ifndef SQUAREGRAPHNODE_H
#define SQUAREGRAPHNODE_H

#include "../Node.h"

class SquareGraphNode : public Node
{
public:
    SquareGraphNode()
    {
        theType = GeomSquareType;
    }
};

#endif // SQUAREGRAPHNODE_H
