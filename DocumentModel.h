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
        return theAuthor;
    }

    void setAuthor(const IAuthor *theAuthor)
    {
        this->theAuthor = const_cast<IAuthor *>(theAuthor); // quirk; must for const-correctness
    }

    void addNode(const INode *theNode);

    void removeNode(const INode *theNode);

    void relate(const IRelation *theRelation, const INode *thisNode, const INode *thatNode);

    void breakUp(const IRelation *theRelation);

protected:
    GraphType theGraph;
    IAuthor *theAuthor;

    vertex_iterator_t findNode(const INode *theNode);
    edge_iterator_t findRelation(const IRelation *theRelation);
};

#endif // DOCUMENTMODEL_H
