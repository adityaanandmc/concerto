#ifndef DOCUMENTMODEL_H
#define DOCUMENTMODEL_H

#include "IDocumentModel.h"

class DocumentModel : public IDocumentModel
{
public:
    explicit DocumentModel(const std::string& theTitle, const std::string& theDescription);

    const GraphType& getGraph() const
    {
        return theGraph;
    }

    void setGraph(const GraphType& theGraph)
    {
        this->theGraph = theGraph;
    }

    const std::string& getTitle() const
    {
        return theGraph[boost::graph_bundle].theTitle;
    }

    void setTitle(const std::string& theTitle)
    {
        theGraph[boost::graph_bundle].theTitle = theTitle;
    }

    const std::string& getDescription() const
    {
        return theGraph[boost::graph_bundle].theDescription;
    }

    void setDescription(const std::string& theDescription)
    {
        theGraph[boost::graph_bundle].theDescription = theDescription;
    }

    const IAuthor *getAuthor() const
    {
        return theAuthor.get();
    }

    IAuthor *grabAuthor() const
    {
        return theAuthor.get();
    }

    void setAuthor(const IAuthor *theAuthor)
    {
        this->theAuthor.reset(const_cast<IAuthor *>(theAuthor)); // quirk; must for const-correctness
    }

    void addNode(const INode *theNode);

    void removeNode(const INode *theNode);

    void relate(const IRelation *theRelation, const INode *thisNode, const INode *thatNode);

    void breakUp(const IRelation *theRelation);

    const INode *getNode(uint16_t theId) const;

    INode *grabNode(uint16_t theId) const;

    const IRelation *getRelation(const INode *thisNode, const INode *thatNode);

    IRelation *grabRelation(const INode *thisNode, const INode *thatNode);

    std::map<IRelation *, INode *> getRelationMap(const INode *theNode);

    std::vector<vertex_t> getTargetVertices(vertex_t theSourceVertex);

    bool validate();

protected:
    GraphType theGraph;
    std::auto_ptr<IAuthor> theAuthor;

    vertex_iterator_t findNode(const INode *theNode);
    edge_iterator_t findRelation(const IRelation *theRelation);
};

#endif // DOCUMENTMODEL_H
