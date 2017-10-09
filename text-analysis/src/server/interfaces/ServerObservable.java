package server.interfaces;


import node.interfaces.MRNode;

/**
 * Created by Wojtek on 15/01/15.
 */
public interface ServerObservable {
    void notifyObservers(MRNode node);
    void attachObserver(ServerObserver object);
    void detachObserver(ServerObserver object);
}

// Observer Pattern - Push Model