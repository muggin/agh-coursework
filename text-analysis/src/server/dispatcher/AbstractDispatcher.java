package server.dispatcher;

import model.commands.interfaces.CommandCallback;
import model.commands.interfaces.CommandFactory;
import server.LoadBalancer;
import model.chunks.Chunk;

import java.io.Serializable;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;

/**
 * Created by Olek on 2015-02-21.
 * Klasa bazowa dla wszystkich dispatcherów.
 * @see server.dispatcher.MapDispatcher
 * @see server.dispatcher.ReduceDispatcher
 */
public abstract class AbstractDispatcher implements Serializable {

    /**
     * Liczba zadań zleconych danemu dispatcherowi
     */
    protected static int requestToBeDone = 0;
    /**
     * Liczba zadań będących w trakcie wykonywania
     */
    protected static int requestsInProgress = 0;
    /**
     * Liczba ukończonych zadań.
     */
    protected static int requestsFinished = 0;


    /**
     * Wykorzystywany LoadBalancer
     */
    protected LoadBalancer loadBalancer;

    /**
     * Wykorzystywana fabryka abstrakcyjna
     */
    protected CommandFactory commandFactory;

    /**
     * Konstruktor klasy Abstract Dispatcher
     * @param lb Load Balancer używany do zlecania zadań
     * @param cf Fabryka komend używana do konstrukcji zleceń
     */
    public AbstractDispatcher( LoadBalancer lb, CommandFactory cf) {
        System.out.println("Dispatcher: constructor");
        this.loadBalancer = lb;
        this.commandFactory = cf;
    }

    /**
     * Zleca dispatcherowi wykonanie wszystkich komend
     */
    public abstract void processAll();

    /**
     * Zleca dispatcherowi wykonanie jednej komendy.
     * @param singleChunkRequest Lista Chunków potrzebna do stworzenia pojedyńczej komendy
     */
    public  void processSingle(ArrayList<? extends Chunk> singleChunkRequest){
        requestsInProgress++;
    }


    /**
     * Klasa bazowa dla Callbacków dispatchera
     */
    public abstract class DispatcherCallback extends UnicastRemoteObject implements CommandCallback {

        DispatcherCallback () throws RemoteException {
            super();
        }

        @Override
        public void commandCompleted(Chunk oldChunk, ArrayList<Chunk> newChunks) {
            requestsInProgress--;
            requestsFinished++;
        }

        @Override
        public void commandFailed(Chunk oldChunk) {
            System.out.println("DispatcherCallback: commandFailed()");
            requestsInProgress--;
        }
    }

}
