//
//  AgentFactory.h
//  Network_Dynamics
//
//  Created by Wojtek on 14/11/14.
//  Copyright (c) 2014 Wojtek. All rights reserved.
//

#ifndef __Network_Dynamics__AgentFactory__
#define __Network_Dynamics__AgentFactory__

#include <iostream>
#include <unordered_map>
#include "Agent.h"
#include "SexTrait.h"
#include "AgeTrait.h"
#include "MeritalStatusTrait.h"
#include "OccupationTrait.h"

class AgentHandler {
private:
    std::unordered_map<long, std::unique_ptr<Agent>> agentStorage;
    
    /**
     AgentHandler class default constructor.
     */
    AgentHandler();
    
    /**
     AgentHandler class copy constructor. (Deleted)
     */
    AgentHandler(const AgentHandler&)=delete;
    
    /** AgentHandler class rvalue copy constructor. (Deleted).
     */
    AgentHandler(AgentHandler&&)=delete;
    
    /**
     AgentHandler class default destructor.
     */
    ~AgentHandler();
    
    /**
     Function generates unique ID's for new agents.
     @return Unique ID generated for agent
     */
    long generateAgentId();
    
    /**
     Function fills out new agent details. Use only after agents initialization.
     @params agentId agent to be setup up
     */
    void setupAgent(Agent& agent);
    
public:
    /**
     Get AgentHandler instance (Singleton class).
     */
    static AgentHandler& getInstance();
    
    /**
     Function creates new agent. Stored in AgentHandler.
     @return Unique agent identifier.
     */
    long createAgent();
    
    /**
     Function removes agent from AgentHandler.
     @param agentId ID of agent to be removed
     @return Boolean indicating if operation was successful
     */
    bool removeAgent(long agentId);
    
    /**
     Function returns a vector o n closest agents to a given agent.
     @param agentId base agent for neighbor search
     @param closesCount number of closest agents
     @return Vector containing ID's of agents that are closest to a given agent.
     */
    std::vector<long> findClosestAgents(long agentId, int closestCount);
        
    /**
     Function compares two agents.
     @param firstAgentId ID of first agent to be compared
     @param secondAgentId ID of second agent to be compared
     @return Value indicating agent similarity
     */
    double compareAgents(long firstAgentId, long secondAgentId);
    
    /**
     Function prints agent details to std output.
     @param agentId ID of printed agent
     */
    void printAgent(long agentId);

};

#endif /* defined(__Network_Dynamics__AgentFactory__) */
