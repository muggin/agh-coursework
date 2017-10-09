package server;

import node.interfaces.MRNode;
import server.interfaces.MRServer;
import server.interfaces.ServerObservable;
import server.interfaces.ServerObserver;

import java.net.UnknownHostException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.LinkedHashSet;

/**
 * Created by Wojtek on 17/02/15.
 */
public class ConnectionHandler implements MRServer, ServerObservable {
    private static ConnectionHandler connectionHandlerInstance = null;
    LinkedHashSet<MRNode> registeredNodes = new LinkedHashSet<>();
    LinkedHashSet<ServerObserver> observers = new LinkedHashSet<>();

    private ConnectionHandler() throws RemoteException {
        System.out.println("ConnectionHandler: constructor");
        try {
            System.setProperty("java.rmi.server.hostname", java.net.InetAddress.getLocalHost().getHostAddress());
            Registry registry = LocateRegistry.createRegistry(1099);
            MRServer stub = (MRServer) UnicastRemoteObject.exportObject(this, 0);
            registry.rebind(MRServer.LOOKUP_NAME, stub);
        } catch (RemoteException e) {
            e.printStackTrace();
            throw new RemoteException("Error while starting server:" + e.toString());
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }
    }

    public static ConnectionHandler getConnectionHandlerInstance() throws RemoteException {
        System.out.println("ConnectionHandler: getConnectionHandlerInstance()");
        if (connectionHandlerInstance == null)
            connectionHandlerInstance = new ConnectionHandler();

        return connectionHandlerInstance;
    }

    @Override
    public void registerNode(MRNode node) {
        System.out.println("ConnectionHandler: registerNode(" + node + ")");
        registeredNodes.add(node);
        notifyObservers(node);
    }

    @Override
    public void removeNode(MRNode node) {
        System.out.println("ConnectionHandler: removeNode()");
    }

    @Override
    public void notifyObservers(MRNode node) {
        System.out.println("ConnectionHandler: notifyObservers()");
        for (ServerObserver o : observers)
            o.update(node);
    }

    @Override
    public void attachObserver(ServerObserver observer) {
        System.out.println("ConnectionHandler: attachObserver()");
        observers.add(observer);
    }

    @Override
    public void detachObserver(ServerObserver observer) {
        System.out.println("ConnectionHandler: detachObserver()");
        observers.remove(observer);
    }
}

// Singleton Pattern