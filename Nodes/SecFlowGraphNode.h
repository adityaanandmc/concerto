#ifndef SECFLOWGRAPHNODE_H
#define SECFLOWGRAPHNODE_H

#include "../Node.h"

class SecFlowGraphNode : public Node
{
public:
    SecFlowGraphNode()
    {
        theType = SecFlowType;
    }
};

#endif // SECFLOWGRAPHNODE_H
