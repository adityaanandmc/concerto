#ifndef ACTORGRAPHNODE_H
#define ACTORGRAPHNODE_H

#include "../Node.h"

class ActorGraphNode : public Node
{
public:
    ActorGraphNode()
    {
        theType = ActorType;
    }
};

#endif // ACTORGRAPHNODE_H
