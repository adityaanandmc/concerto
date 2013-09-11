#ifndef ALTFLOWGRAPHNODE_H
#define ALTFLOWGRAPHNODE_H

#include "../Node.h"

class AltFlowGraphNode : public Node
{
public:
    AltFlowGraphNode()
    {
        theType = AltFlowType;
    }
};

#endif // ALTFLOWGRAPHNODE_H
