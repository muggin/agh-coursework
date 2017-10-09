//
//  SocialNetworkHeader.h
//  Network_Dynamics
//
//  Created by Wojciech Kryscinski on 03/12/14.
//  Copyright (c) 2014 Wojtek. All rights reserved.
//

#ifndef Network_Dynamics_SocialNetworkHeader_h
#define Network_Dynamics_SocialNetworkHeader_h

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graphviz.hpp>

struct vertex_info {
    long vertex_id;
    int weight_pool;
};

struct edge_info {
    long edge_weight;
    size_t index;
};

typedef boost::adjacency_list<boost::setS, boost::vecS, boost::undirectedS,vertex_info,edge_info> Graph;
//typedef boost::subgraph< boost::adjacency_list<boost::setS, boost::vecS, boost::undirectedS, boost::property<boost::vertex_index_t, int>, boost::property<boost::edge_index_t, int>>> Graph; <- bardzo chcemy
//typedef boost::subgraph< boost::adjacency_list<boost::setS, boost::vecS, boost::undirectedS, vertex_info, edge_info>> SubGraph;
typedef boost::graph_traits<Graph>::vertex_iterator VertexIterator;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;
#endif
