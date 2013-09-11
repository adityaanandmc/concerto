#ifndef SUBFLOWGRAPHNODE_H
#define SUBFLOWGRAPHNODE_H

#include "../Node.h"

class SubFlowGraphNode : public Node
{
public:
    SubFlowGraphNode()
    {
        theType = SubFlowType;
    }
};

#endif // SUBFLOWGRAPHNODE_H
