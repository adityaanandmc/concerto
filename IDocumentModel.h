#ifndef IDOCUMENTMODEL_H
#define IDOCUMENTMODEL_H

#include "GraphDefs.h"
#include "IDiagram.h"

struct IDocumentModel : public IDiagram
{
    virtual ~IDocumentModel() {}

    virtual const GraphType& getGraph() const = 0;

    virtual void setGraph(const GraphType& theGraph) = 0;

    virtual void addNode(const INode *theNode) = 0;

    virtual void removeNode(const INode *theNode) = 0;

    virtual void relate(const IRelation *theRelation, const INode *thisNode, const INode *thatNode) = 0;

    virtual void breakUp(const IRelation *theRelation) = 0;
};

#endif // IDOCUMENTMODEL_H