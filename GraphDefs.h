#ifndef GRAPHDEFS_H
#define GRAPHDEFS_H

#include <boost/graph/adjacency_list.hpp>

#include "Graph/DiagramInfo.h"
#include "Graph/Vertex.h"
#include "Graph/Edge.h"

typedef boost::adjacency_list<
    boost::listS, boost::vecS, boost::bidirectionalS,
    Vertex, Edge, DiagramInfo
    > GraphType;

typedef boost::graph_traits<GraphType>::vertex_descriptor vertex_t;
typedef boost::graph_traits<GraphType>::edge_descriptor edge_t;
typedef boost::graph_traits<GraphType>::vertex_iterator vertex_iterator_t;
typedef boost::graph_traits<GraphType>::edge_iterator edge_iterator_t;

#endif // GRAPHDEFS_H
