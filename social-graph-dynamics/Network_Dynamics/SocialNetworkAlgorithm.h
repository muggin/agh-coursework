//
//  SocialNetworkAlgorithm.h
//  Social Network
//
//  Created by Aleksander Wójcik on 01.12.2014.
//  Copyright (c) 2014 Aleksander Wójcik. All rights reserved.
//

#ifndef __Social_Network__SocialNetworkAlgorithm__
#define __Social_Network__SocialNetworkAlgorithm__

#include <iostream>
#include <vector>
#include <boost/foreach.hpp>
#include "SocialNetworkGraph.h"
template <typename K, typename V>
V GetWithDef(const  std::map <K,V> & m, const K & key, const V & defval ) {
    typename std::map<K,V>::const_iterator it = m.find( key );
    if ( it == m.end() ) {
        return defval;
    }
    else {
        return it->second;
    }
}
struct SimillarityComparator {
    bool operator() (std::pair<long,double> i,std::pair<long,double> j) { return (i.second>j.second);}
};

class SocialNetworkAlgorithm{
private:
    SocialNetworkGraph& socialNetorkGraph;
    void limitedDFS(long startId, long currentId,int DFSlimit,int currentLevel,std::vector<std::pair<long, double>>& retVector,std::map<long,bool>& visitMap);
    
public:
    SocialNetworkAlgorithm(SocialNetworkGraph& graph):socialNetorkGraph(graph){}
    std::vector<std::pair<long,double>> getIdDistancePairs(long startdId,int DFSlimit);
    
    void makeMove(double DFSprobability,int DFSlimit,int oneNodeConnections);
    
    void makeRandomConnections(int randomConnectionCount);
    
    class NetworkVisitor:public boost::default_dfs_visitor {
    private:
        int curentDepthCount;
        int maxDepth;
    public:
        NetworkVisitor(int maxDepth);
        void discover_vertex(boost::graph_traits<Graph>::vertex_descriptor u, Graph g);
        void finish_vertex(boost::graph_traits<Graph>::vertex_descriptor u, Graph g);
        bool operator()();
    };
    

};

#endif /* defined(__Social_Network__SocialNetworkAlgorithm__) */
