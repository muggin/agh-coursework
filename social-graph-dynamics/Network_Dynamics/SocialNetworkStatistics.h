//
//  SocialNetworkStatistics.h
//  Network_Dynamics
//
//  Created by Wojciech Kryscinski on 03/12/14.
//  Copyright (c) 2014 Wojtek. All rights reserved.
//

#ifndef __Network_Dynamics__SocialNetworkStatistics__
#define __Network_Dynamics__SocialNetworkStatistics__

#include <iostream>
#include <vector>
#include <map>
#include <boost/graph/subgraph.hpp>
#include <boost/graph/clustering_coefficient.hpp>
#include <boost/graph/geodesic_distance.hpp>
#include <boost/graph/floyd_warshall_shortest.hpp>
#include <boost/graph/exterior_property.hpp>
#include "SocialNetworkHeaders.h"

typedef boost::exterior_vertex_property<Graph, float> AlgorithmProperty;
typedef AlgorithmProperty::container_type AlgorithmContainer;
typedef AlgorithmProperty::map_type AlgorithmMap;
typedef boost::exterior_vertex_property<Graph, int> DistanceProperty;
typedef DistanceProperty::matrix_type DistanceMatrix;
typedef DistanceProperty::matrix_map_type DistanceMatrixMap;
typedef boost::constant_property_map<Edge, int> WeightMap;

class SocialNetworkStatistics {
private:
    /*
     Graph on which statistics will be performed
     */
    const Graph& graph;
    
    /* 
     Average vertex degree in analyzed graph.
     */
    double degreeAverage;
    
    /*
     Clustering coefficient in analyzed graph.
     */
    double clusteringCoefficient;
    
    /*
     Average small world distance between vertices.
     */
    double smallWorldDistance;
    
    /*
     Vertex degree histogram.
     */
    std::map<unsigned long, int> degreeHistogram;
    
    void calculateDegreeHistogram(const Graph& analyzedGraph);
    void calculateClusteringCoefficient(const Graph& analyzedGraph);
    void calculateMeanGeodesicDistance(const Graph& analyzedGraph);
    
public:
    SocialNetworkStatistics(const Graph& graphReference);
    void calculateStatistics();
    void printStatistics();
    const std::map<unsigned long, int>& getHistogram();
    

    
};

#endif /* defined(__Network_Dynamics__SocialNetworkStatistics__) */
