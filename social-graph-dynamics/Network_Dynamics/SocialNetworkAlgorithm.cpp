//
//  SocialNetworkAlgorithm.cpp
//  Social Network
//
//  Created by Aleksander Wójcik on 01.12.2014.
//  Copyright (c) 2014 Aleksander Wójcik. All rights reserved.
//

#include "SocialNetworkAlgorithm.h"

std::vector<std::pair<long,double>> SocialNetworkAlgorithm::getIdDistancePairs(long startId,int DFSlimit){
    std::vector<std::pair<long, double>> retVector;
    std::map<long,bool> isVisited;
    isVisited[startId]=true;
    Graph::adjacency_iterator vertexIt, vertexEnd;
    boost::tie(vertexIt, vertexEnd) = adjacent_vertices( socialNetorkGraph.idToVdMap[startId], socialNetorkGraph.mGraph );
    for (; vertexIt != vertexEnd; ++vertexIt){
        limitedDFS(startId,socialNetorkGraph.mGraph[(*vertexIt)].vertex_id,DFSlimit,1,retVector,isVisited);
    }
    SimillarityComparator comp;
    std::sort (retVector.begin(), retVector.end(), comp);
    return retVector;
}

void SocialNetworkAlgorithm::limitedDFS(long startId,long currentId, int DFSlimit,int currentLevel,std::vector<std::pair<long, double>>& retVector,std::map<long,bool>& visitMap){
    bool wasVisited=GetWithDef(visitMap,currentId,false);
    if(wasVisited==true||currentLevel>DFSlimit){
        return;
    }
    visitMap[currentId]=true;
    std::pair<Graph::edge_descriptor, bool> edge=boost::edge(socialNetorkGraph.idToVdMap[startId],socialNetorkGraph.idToVdMap[currentId],socialNetorkGraph.mGraph);
    if(currentLevel!=1&&edge.second==false){
        retVector.push_back(std::pair<long,double>(currentId,AgentHandler::getInstance().compareAgents(startId,currentId)));
    }
    Graph::adjacency_iterator vertexIt, vertexEnd;
    boost::tie(vertexIt, vertexEnd) = adjacent_vertices( socialNetorkGraph.idToVdMap[currentId], socialNetorkGraph.mGraph );
    for (; vertexIt != vertexEnd; ++vertexIt){
        limitedDFS(startId,socialNetorkGraph.mGraph[(*vertexIt)].vertex_id,DFSlimit,currentLevel+1,retVector,visitMap);
    }
    
}

void SocialNetworkAlgorithm::makeMove(double DFSprobability,int DFSlimit,int oneNodeConnections){
    typedef std::map<long,Graph::vertex_descriptor> map_t;
    BOOST_FOREACH( map_t::value_type& pair, socialNetorkGraph.idToVdMap)
    {
        if(rand()%1000<DFSprobability*1000){
            
            std::vector<std::pair<long,double>> bestMatches=getIdDistancePairs(pair.first,DFSlimit);
            std::vector<std::pair<long,double>>::iterator start,currentIt;
            start=currentIt=bestMatches.begin();
            for(;currentIt!=bestMatches.end()&&(currentIt-start)<oneNodeConnections;currentIt++){
                socialNetorkGraph.addEdge(pair.first, (*currentIt).first);
                //cout<<"Adding edge "<<pair.first<<"-"<<(*currentIt).first<<endl;
            }
        }
    }
}


SocialNetworkAlgorithm::NetworkVisitor::NetworkVisitor(int maxDepth){
    this->maxDepth=maxDepth;
    curentDepthCount=0;
}

void SocialNetworkAlgorithm::NetworkVisitor::discover_vertex(boost::graph_traits<Graph>::vertex_descriptor u, Graph g){
    //cout<<"discover vertex called current Depth "<<curentDepthCount<<endl;
    curentDepthCount++;
}

void SocialNetworkAlgorithm::NetworkVisitor::finish_vertex(boost::graph_traits<Graph>::vertex_descriptor u, Graph g){
    //cout<<"finish vertex called current Depth "<<curentDepthCount<<endl;
    curentDepthCount--;
}

bool SocialNetworkAlgorithm::NetworkVisitor::operator()(){
    if(curentDepthCount+1>maxDepth){
        return true;
    }
    else{
        return false;
    }
}

void SocialNetworkAlgorithm::makeRandomConnections(int randomConnectionCount){
    long firstID,secondId;
    
    for(int i=0;i<randomConnectionCount;i++){
        firstID = socialNetorkGraph.getRandomId();
        secondId = socialNetorkGraph.getRandomId();
        
        if(firstID!=secondId){
            socialNetorkGraph.addEdge(firstID, secondId);
        }
    }
}