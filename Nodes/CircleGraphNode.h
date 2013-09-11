#ifndef CIRCLEGRAPHNODE_H
#define CIRCLEGRAPHNODE_H

#include "../Node.h"

class CircleGraphNode : public Node
{
public:
    CircleGraphNode()
    {
        theType = GeomCircleType;
    }
};

#endif // CIRCLEGRAPHNODE_H
