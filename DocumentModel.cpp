#include "DocumentModel.h"
#include "IIdentifiable.h"

DocumentModel::DocumentModel(const std::string &theTitle, const std::string &theDescription)
{
    theGraph[boost::graph_bundle].theDescription = theDescription;
    theGraph[boost::graph_bundle].theTitle = theTitle;
}

void DocumentModel::addNode(const INode *theNode)
{
    vertex_t theVertex = boost::add_vertex(theGraph);

    theGraph[theVertex].theNode = const_cast<INode *>(theNode);
}

void DocumentModel::removeNode(const INode *theNode)
{
    vertex_iterator_t vi, vi_end, next;

    boost::tie(vi, vi_end) = boost::vertices(theGraph);
    for (next = vi; vi != vi_end; vi = next) {
        ++next;
        if (theNode == theGraph[*vi].theNode) {
            boost::remove_vertex(*vi, theGraph);
            break;
        }
    }
}

void DocumentModel::relate(const IRelation *theRelation, const INode *thisNode, const INode *thatNode)
{
    vertex_iterator_t thisKey = findNode(thisNode), thatKey = findNode(thatNode), end = boost::vertices(theGraph).second;

    if (end == thisKey) {
        throw "Owning side of the relation does not exist!";
    }

    if (end == thatKey) {
        throw "Target of the relation does not exist!";
    }

    vertex_t thisVertex = *thisKey, thatVertex = *thatKey;
    edge_t theEdge;
    bool status;

    boost::tie(theEdge, status) = boost::add_edge(thisVertex, thatVertex, theGraph);

    if (false == status) {
        throw "These nodes are already related!";
    }

    theGraph[theEdge].theRelation = const_cast<IRelation *>(theRelation);
}

void DocumentModel::breakUp(const IRelation *theRelation)
{
    edge_iterator_t theEdge = findRelation(theRelation), end = boost::edges(theGraph).second;

    if (end == theEdge) {
        throw "The specified relation doesn't seem to exist!";
    }

    boost::remove_edge(*theEdge, theGraph);
}

const INode *DocumentModel::getNode(uint16_t theId) const
{
    vertex_iterator_t vi, vi_end, next;

    boost::tie(vi, vi_end) = boost::vertices(theGraph);
    for (next = vi; vi != vi_end; vi = next) {
        ++next;
        if (IIdentifiable *theNode = dynamic_cast<IIdentifiable *>(theGraph[*vi].theNode)) {
            if (theId == theNode->getId()) {
                return theGraph[*vi].theNode;
            }
        }
    }

    return NULL;
}

INode *DocumentModel::grabNode(uint16_t theId) const
{
    vertex_iterator_t vi, vi_end, next;

    boost::tie(vi, vi_end) = boost::vertices(theGraph);
    for (next = vi; vi != vi_end; vi = next) {
        ++next;
        if (IIdentifiable *theNode = dynamic_cast<IIdentifiable *>(theGraph[*vi].theNode)) {
            if (theId == theNode->getId()) {
                return theGraph[*vi].theNode;
            }
        }
    }

    return NULL;
}

const IRelation *DocumentModel::getRelation(const INode *thisNode, const INode *thatNode)
{
    edge_t theEdge;
    bool status;

    vertex_t thisVertex = *findNode(thisNode), thatVertex = *findNode(thatNode);

    boost::tie(theEdge, status) = boost::edge(thisVertex, thatVertex, theGraph);

    if (true == status) {
        return theGraph[theEdge].theRelation;
    }

    return NULL;
}

IRelation *DocumentModel::grabRelation(const INode *thisNode, const INode *thatNode)
{
    edge_t theEdge;
    bool status;

    vertex_t thisVertex = *findNode(thisNode), thatVertex = *findNode(thatNode);

    boost::tie(theEdge, status) = boost::edge(thisVertex, thatVertex, theGraph);

    if (true == status) {
        return theGraph[theEdge].theRelation;
    }

    return NULL;
}

vertex_iterator_t DocumentModel::findNode(const INode *theNode)
{
    vertex_iterator_t vi, vi_end, next;

    boost::tie(vi, vi_end) = boost::vertices(theGraph);
    for (next = vi; vi != vi_end; vi = next) {
        ++next;
        if (theNode == theGraph[*vi].theNode) {
            return vi;
        }
    }

    return vi_end;
}

edge_iterator_t DocumentModel::findRelation(const IRelation *theRelation)
{
    edge_iterator_t ei, ei_end, next;

    boost::tie(ei, ei_end) = boost::edges(theGraph);
    for (next = ei; ei != ei_end; ei = next) {
        ++next;
        if (theRelation == theGraph[*ei].theRelation) {
            return ei;
        }
    }

    return ei_end;
}
