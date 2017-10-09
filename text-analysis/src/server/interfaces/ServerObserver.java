package server.interfaces;

import node.interfaces.MRNode;

/**
 * Created by Wojtek on 15/01/15.
 */
public interface ServerObserver {
    public void update(MRNode node);
}


// Observer Pattern - Push Model