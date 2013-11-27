#ifndef IDOCUMENTMODEL_H
#define IDOCUMENTMODEL_H

#include "GraphDefs.h"
#include "IDiagram.h"

#include <stdint.h>

struct IDocumentModel : public IDiagram
{
    virtual ~IDocumentModel() {}

    virtual const GraphType& getGraph() const = 0;

    virtual void setGraph(const GraphType& theGraph) = 0;

    virtual void addNode(const INode *theNode) = 0;

    virtual void removeNode(const INode *theNode) = 0;

    virtual void relate(const IRelation *theRelation, const INode *thisNode, const INode *thatNode) = 0;

    virtual void breakUp(const IRelation *theRelation) = 0;

    virtual const INode *getNode(uint16_t theId) const = 0;

    virtual INode *grabNode(uint16_t theId) const = 0;

    virtual const IRelation *getRelation(const INode *thisNode, const INode *thatNode) = 0;

    virtual IRelation *grabRelation(const INode *thisNode, const INode *thatNode) = 0;

    virtual std::map<IRelation *, INode *> getRelationMap(const INode *theNode) = 0;

    virtual std::vector<vertex_t> getTargetVertices(vertex_t theSourceVertex) = 0;

    virtual bool validate() = 0;
};

#endif // IDOCUMENTMODEL_H
