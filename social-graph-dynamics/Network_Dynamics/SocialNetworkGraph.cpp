//
//  SocialNetworkGraph.cpp
//  Social Network
//
//  Created by Aleksander Wójcik on 15.11.2014.
//  Copyright (c) 2014 Aleksander Wójcik. All rights reserved.
//

#include <iostream>
#include "SocialNetworkGraph.h"
#include "AgentHandler.h"

using namespace std;


void SocialNetworkGraph::addAgent(long id){
    Graph::vertex_descriptor v = boost::add_vertex(mGraph);
    mGraph[v].vertex_id=id;
    mGraph[v].weight_pool=rand()%(maxWeightPool-minWeightPool)+minWeightPool;
//   std::cout<<"Agent "<<id<<" weigh pool "<<mGraph[v].weight_pool<<endl;
    idToVdMap.insert(std::pair<long,Graph::vertex_descriptor>(id,v));
}

void SocialNetworkGraph::addEdge(long idAgent1,long idAgent2){
    Graph::vertex_descriptor v1=idToVdMap[idAgent1];
    Graph::vertex_descriptor v2=idToVdMap[idAgent2];
    AgentHandler& agenthandler=AgentHandler::getInstance();

    int weightPooled=agenthandler.compareAgents(idAgent1, idAgent2)*multiplyCoefficient;
//    std::cout<<"Adding edge weight Poooled "<<weightPooled<<endl;
    
    if(mGraph[v1].weight_pool-weightPooled<0){
        while(mGraph[v1].weight_pool-weightPooled<0){
//            std::cout<<"Before iteration v1 current pool "<<mGraph[v1].weight_pool<<" Ammount needed: "<<weightPooled<<endl;
            adjustEdges(v1,std::abs(mGraph[v1].weight_pool-weightPooled));
//            std::cout<<"Loop iteration done current pool "<<mGraph[v1].weight_pool<<endl;
        }
//        std::cout<<"Adjusting done current pool "<<mGraph[v1].weight_pool<<endl;
    }
    else if(mGraph[v2].weight_pool-weightPooled<0){
        while(mGraph[v2].weight_pool-weightPooled<0){
//            std::cout<<"Before iteration v2 current pool "<<mGraph[v2].weight_pool<<" Ammount needed: "<<weightPooled<<endl;
            adjustEdges(v2,std::abs(mGraph[v2].weight_pool-weightPooled));
//            std::cout<<"Loop iteration done current pool "<<mGraph[v2].weight_pool<<endl;
        }
//        std::cout<<"Adjusting done current pool "<<mGraph[v2].weight_pool<<endl;
    }
    
    boost::add_edge(v1,v2,mGraph);
    std::pair<Graph::edge_descriptor, bool> edgePair = boost::edge(v1, v2, mGraph);
    mGraph[edgePair.first].edge_weight=weightPooled;
    mGraph[v1].weight_pool-=weightPooled;
    mGraph[v2].weight_pool-=weightPooled;
}

void SocialNetworkGraph::adjustEdges(Graph::vertex_descriptor v,int weightDifference){
//    std::cout<<"Adjusting edges for "<<mGraph[v].vertex_id<<" current pool: "<<mGraph[v].weight_pool<<" difference "<<weightDifference<<endl;
    unsigned long vertexDegree=boost::degree(v,mGraph);
    
    int eachPoolDiff=(weightDifference/vertexDegree)+1;
    std::vector<pair<Graph::vertex_descriptor,Graph::vertex_descriptor> > toRemove;
    
    Graph::adjacency_iterator vertexIt, vertexEnd;
    boost::tie(vertexIt, vertexEnd) = adjacent_vertices( v, mGraph );
    for (; vertexIt != vertexEnd; ++vertexIt){
        std::pair<Graph::edge_descriptor, bool> edgePair = boost::edge(v, *vertexIt, mGraph);
        if(mGraph[edgePair.first].edge_weight-eachPoolDiff<0){
//            std::cout<<"Removing edge"<<endl;
            toRemove.push_back(pair<Graph::vertex_descriptor,Graph::vertex_descriptor>(v,*vertexIt));
        }
        else{
//            std::cout<<"Adding "<<eachPoolDiff<<" to "<<mGraph[v].vertex_id<< " and "<<mGraph[*vertexIt].vertex_id<<endl;
            mGraph[edgePair.first].edge_weight-=eachPoolDiff;
            mGraph[v].weight_pool+=eachPoolDiff;
            mGraph[*vertexIt].weight_pool+=eachPoolDiff;
        }
    }
    
    for(std::vector<pair<Graph::vertex_descriptor,Graph::vertex_descriptor> > ::iterator it=toRemove.begin();it!=toRemove.end();it++){
        removeEdge(mGraph[(*it).first].vertex_id, mGraph[(*it).second].vertex_id);
    }
}

void SocialNetworkGraph::removeEdge(long id1, long id2){
    Graph::vertex_descriptor v1=idToVdMap[id1];
    Graph::vertex_descriptor v2=idToVdMap[id2];
    
    std::pair<Graph::edge_descriptor, bool> edgePair = boost::edge(v1, v2, mGraph);
    
    mGraph.remove_edge(edgePair.first);
}

SocialNetworkGraph::SocialNetworkGraph() : socialNetworkStatistics(mGraph) {
}



void SocialNetworkGraph::generateGraphiz(std::ostream& stream){
    //std::ofstream dotfile (filename);
    boost::dynamic_properties dp;
    dp.property("node_id", boost::get(&vertex_info::vertex_id, mGraph));
    write_graphviz_dp(stream,mGraph,dp);
}

void SocialNetworkGraph::removeAgent(long id){
    Graph::vertex_descriptor v=idToVdMap[id];
    boost::clear_vertex(v,mGraph);
    boost::remove_vertex(v, mGraph);
    idToVdMap.erase(id);
}

void SocialNetworkGraph::generateRandomSocialGraph(long nodes,long maxConnections){
    AgentHandler& handler=AgentHandler::getInstance();
    long nextId;
    for(long i=0;i<nodes;i++){
        nextId=handler.createAgent();
        addAgent(nextId);
    }
    long thisConnections;
    long connectedId;
    for (std::map<long,Graph::vertex_descriptor>::iterator it=idToVdMap.begin(); it!=idToVdMap.end(); ++it){
        nextId=it->first;
        thisConnections=rand()%(maxConnections+1);
        for(long i=0;i<thisConnections;i++){
            connectedId=getRandomId();
            if(nextId!=connectedId){
                addEdge(nextId, connectedId);
            }
        }
        
    }
}

void SocialNetworkGraph::generateSmallWorldSocialGraph(long nodes, int connections,int maxRandomConnections,int randomConnectionProbability){
    AgentHandler& handler=AgentHandler::getInstance();
    long nextId;
    long randomVertexId;
    int thisVertexRandom;
    int currentVertexRandomCount;
    std::vector<long> closestIds;
    
    
    for(long i=0;i<nodes;i++){
        nextId=handler.createAgent();
        addAgent(nextId);
    }
    
    for (std::map<long,Graph::vertex_descriptor>::iterator it=idToVdMap.begin(); it!=idToVdMap.end(); ++it){
        nextId=it->first;
        closestIds=handler.findClosestAgents(nextId, connections);
        for(std::vector<long>::iterator vIt=closestIds.begin();vIt!=closestIds.end();vIt++){
            addEdge(nextId, *vIt);
        }
    }
    
    for (std::map<long,Graph::vertex_descriptor>::iterator it=idToVdMap.begin(); it!=idToVdMap.end(); ++it){
        nextId=it->first;
        thisVertexRandom=rand()%100;
        if(thisVertexRandom<randomConnectionProbability){
            currentVertexRandomCount=(rand()%maxRandomConnections)+1;
            for(int i=0;i<currentVertexRandomCount;i++){
                randomVertexId=getRandomId();
                if(randomVertexId!=nextId){
                    addEdge(nextId, randomVertexId);
                }
            }
        }
    }
    
}


long SocialNetworkGraph::getRandomId(){
    long mapSize=idToVdMap.size();
    std::map<long,Graph::vertex_descriptor>::iterator it=idToVdMap.begin();
    std::advance(it,rand()%mapSize);
    return it->second;
}







