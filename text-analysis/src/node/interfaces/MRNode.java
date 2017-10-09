package node.interfaces;

import model.commands.interfaces.Command;

import java.io.Serializable;
import java.rmi.*;

public interface MRNode extends Remote, Serializable {
    public static final String LOOKUP_NAME = "MRNode";

    // Map i Reduce nie przyjmuja poki co argumentow
    // bo nie wiem jeszcze w jakim formacie
    public void placeCommand(Command command) throws RemoteException;
}

// Command Pattern - Invoker
