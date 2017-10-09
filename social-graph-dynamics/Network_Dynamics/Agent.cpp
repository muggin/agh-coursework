//
//  Agent.cpp
//  Network_Dynamics
//
//  Created by Wojtek on 14/11/14.
//  Copyright (c) 2014 Wojtek. All rights reserved.
//

#include "Agent.h"
#include <assert.h>
using namespace std;

Agent::Agent(long agentId) {
    this->agentId = agentId;
    this->traits = vector<unique_ptr<Trait>>();
    this->desirability = vector<int>();
}


double Agent::compareWithAgent(const Agent& otherAgent) const {
    double similarityRate = 0.0;
    
    //TODO More advanced method of computing similarity between agents.
    for (int i = 0; i < this->traits.size(); i++) {
        similarityRate += ((*this->traits[i]) && (*otherAgent.traits[i])) * this->desirability[i];
    }
    
    return similarityRate / this->desirabilitySum;
}

double Agent::operator&& (const Agent& otherAgent) const {
    return this->compareWithAgent(otherAgent);
}

ostream& operator<< (ostream& os, const Agent& agent) {
    os << "AgentID: " << agent.agentId << endl;
    for (auto const& trait : agent.traits) {
        os << *trait << endl;
    }
    return os << endl;
}
