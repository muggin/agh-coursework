package node;

import model.commands.interfaces.Command;
import node.interfaces.MRNode;

import java.rmi.RemoteException;

/**
 * Created by Wojtek on 18/02/15.
 */
public abstract class NodeDecorator implements MRNode {
    protected final MRNode node;

    public NodeDecorator(MRNode node) {
        this.node = node;
    }

    public void placeCommand(Command command) throws RemoteException {
        node.placeCommand(command);
    }
}

// Decorator Pattern - Decorator