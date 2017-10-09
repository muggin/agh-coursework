package node;

import model.commands.interfaces.Command;
import node.interfaces.MRNode;
import server.interfaces.MRServer;

import java.io.File;
import java.nio.file.Paths;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * Created by Wojtek on 17/02/15.
 */
public class Node extends UnicastRemoteObject implements MRNode {
    ExecutorService executorService;
    String tempDirectoryPath;
    String serverAddress;

    public Node() throws RemoteException {
        this("localhost", Paths.get(".").toAbsolutePath().normalize().toString(), 5);
        System.out.println("Node: constuctor");
    }
    public Node(String serverAddress, String tempDirectoryPath, int threadPoolSize) throws RemoteException {
        System.out.println("Node: constuctor");
        this.serverAddress = serverAddress;
        this.tempDirectoryPath = tempDirectoryPath;
        this.executorService = Executors.newFixedThreadPool(threadPoolSize);
        prepareTempDirectories();
    }

    @Override
    public void placeCommand(Command command) {
        System.out.println("Node: placeCommand(" + command + ")");
        Runnable runnableCommand = () -> {
            command.preExecution(tempDirectoryPath);
            command.execute();
            command.postExecution();
        };
        executorService.execute(runnableCommand);
    }

    public void registerNode() throws RemoteException, NotBoundException {
        Registry registry = LocateRegistry.getRegistry(this.serverAddress);
        MRServer serverStub = (MRServer) registry.lookup(MRServer.LOOKUP_NAME);
        serverStub.registerNode(this);
    }

    private void prepareTempDirectories() {
        Date dNow = new Date( );
        SimpleDateFormat ft = new SimpleDateFormat ("/hhmmssSS");
        tempDirectoryPath += ft.format(dNow);

        new File(tempDirectoryPath).mkdir();
        new File(tempDirectoryPath + "/mapper/").mkdir();
        new File(tempDirectoryPath + "/reducer/").mkdir();
    }

    private void removeTempDirectories() {
        new File(tempDirectoryPath + "/mapper/").delete();
        new File(tempDirectoryPath + "/reducer/").delete();
        new File(tempDirectoryPath).delete();
    }

    public static void main (String[] args) {
        try {
            new Node().registerNode();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

// Command Pattern - Invoker
// Thread Pool / Command Queue