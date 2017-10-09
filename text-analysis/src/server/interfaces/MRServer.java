package server.interfaces;

import java.rmi.Remote;
import java.rmi.RemoteException;

import node.interfaces.MRNode;

/**
 * Created by Wojtek on 17/02/15.
 */

public interface MRServer extends Remote {
    public static final String LOOKUP_NAME = "MRServer";

    public void registerNode(MRNode node) throws RemoteException;
    public void removeNode(MRNode node) throws RemoteException;

}
