//
//  AgentFactory.cpp
//  Network_Dynamics
//
//  Created by Wojtek on 14/11/14.
//  Copyright (c) 2014 Wojtek. All rights reserved.
//

#include "AgentHandler.h"
#include <array>


using namespace std;

AgentHandler::AgentHandler() {}

AgentHandler::~AgentHandler() {
    this->agentStorage.clear();
}

AgentHandler& AgentHandler::getInstance() {
    static AgentHandler instance;
    return instance;
}

long AgentHandler::generateAgentId() {
    static long nextId = 0;
    return ++nextId;
}

long AgentHandler::createAgent() {
    long agentId = this->generateAgentId();
    unique_ptr<Agent> newAgent (new Agent(agentId));
    AgentHandler::setupAgent(*newAgent);
    
    this->agentStorage[agentId] = move(newAgent);
    return agentId;
}

void AgentHandler::setupAgent(Agent& agent) {
    int totalDesirability = 0;
    int currentDesirability = 0;
    
    agent.traits.push_back(unique_ptr<Trait>(new SexTrait));
    agent.traits.push_back(unique_ptr<Trait> (new AgeTrait));
    agent.traits.push_back(unique_ptr<Trait> (new OccupationTrait));
    agent.traits.push_back(unique_ptr<Trait> (new MeritalStatusTrait));
    
    for (int i = 0; i < agent.traits.size(); ++i) {
        currentDesirability = rand() % 21;
        totalDesirability += currentDesirability;
        agent.desirability.push_back(currentDesirability);
        agent.desirabilitySum = totalDesirability;
    }
}

bool AgentHandler::removeAgent(long agentId) {
    size_t agentsRemoved = this->agentStorage.erase(agentId);
    return agentsRemoved == 0 ? true : false;
}

std::vector<long> AgentHandler::findClosestAgents(long agentId, int closestCount) {
    auto const& agent = *this->agentStorage[agentId];
    vector<double> highScores(closestCount, 0.0);
    vector<long> closestAgents(closestCount, 0L);
    auto replaceFunction = [&] (double similarity, long agentId) {
        auto minIter = min_element(highScores.begin(), highScores.end());
        if(similarity > *minIter) {
            *minIter = similarity;
            long minIndex = minIter - highScores.begin();
            closestAgents[minIndex] = agentId;
        }
    };
    
    for (auto const& currentAgentPair : this->agentStorage) {
        const Agent& currentAgent = *currentAgentPair.second;
        if (currentAgent.agentId == agentId) {
            continue;
        } else {
            double similarity = agent.compareWithAgent(currentAgent);
            replaceFunction(similarity, currentAgent.agentId);
        }
    }
    return closestAgents;
}

double AgentHandler::compareAgents(long firstAgentId, long secondAgentId) {
    double firstAgentPerspectiveScore = *(this->agentStorage[firstAgentId]) && *(this->agentStorage[secondAgentId]);
    double secondAgentPerspectiveScore = *(this->agentStorage[secondAgentId]) && *(this->agentStorage[firstAgentId]);
    return (firstAgentPerspectiveScore + secondAgentPerspectiveScore) / 2.0;
}

void AgentHandler::printAgent(long agentId) {
    cout << *(this->agentStorage[agentId]);
}

