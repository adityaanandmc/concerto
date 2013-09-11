#ifndef RECTANGLEGRAPHNODE_H
#define RECTANGLEGRAPHNODE_H

#include "../Node.h"

class RectangleGraphNode : public Node
{
public:
    RectangleGraphNode()
    {
        theType = GeomRectangleType;
    }
};

#endif // RECTANGLEGRAPHNODE_H
