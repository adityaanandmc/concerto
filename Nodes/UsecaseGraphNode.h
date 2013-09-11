#ifndef USECASEGRAPHNODE_H
#define USECASEGRAPHNODE_H

#include "../Node.h"

class UsecaseGraphNode : public Node
{
public:
    UsecaseGraphNode()
    {
        theType = UsecaseType;
    }
};

#endif // USECASEGRAPHNODE_H
