package server;

import node.interfaces.MRNode;
import node.RegisteredNode;
import server.interfaces.ServerObserver;

import java.io.Serializable;
import java.util.PriorityQueue;

/**
 * Created by Wojtek on 17/02/15.
 */
public class LoadBalancer implements ServerObserver, Serializable {
    PriorityQueue<RegisteredNode> registeredNodes = new PriorityQueue<>();

    public LoadBalancer() {
        System.out.println("LoadBalancer: constructor");
    }

    public int nodeCount(){
        return registeredNodes.size();
    }

    @Override
    public void update(MRNode node) {
        System.out.println("LoadBalancer: update()");
        registeredNodes.add(new RegisteredNode(node));
    }

    public RegisteredNode assignNode() {
        // Inkrementuj licznik scheduled jobs;
        RegisteredNode assignedNode = registeredNodes.poll();
        assignedNode.incrementAssignCounter();
        registeredNodes.add(assignedNode);
        return assignedNode;
    }

    public void setNode(RegisteredNode node) {
        node.incrementFinishedCounter();
        registeredNodes.remove(node);
        registeredNodes.add(node);
    }

}

// Sponsor-Selector Pattern - Sponsor (RegisteredNode), Selector (LoadBalancer)