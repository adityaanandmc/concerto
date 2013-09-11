#ifndef TRIANGLEGRAPHNODE_H
#define TRIANGLEGRAPHNODE_H

#include "../Node.h"

class TriangleGraphNode : public Node
{
public:
    TriangleGraphNode()
    {
        theType = GeomTriangleType;
    }
};

#endif // TRIANGLEGRAPHNODE_H
