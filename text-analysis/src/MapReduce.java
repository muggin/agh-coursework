import java.io.IOException;
import java.nio.file.Paths;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

import model.chunks.Chunk;
import node.Node;
import model.commands.interfaces.CommandFactory;
import map_reduce_example.ExampleFactory;
import server.ConnectionHandler;
import server.Grouper;
import server.LoadBalancer;
import server.utils.Splitter;
import server.dispatcher.MapDispatcher;
import server.dispatcher.ReduceDispatcher;
import model.chunks.FileChunk;
import model.chunks.MappedChunk;
import model.chunks.ReducedChunk;

/**
 * Created by Wojtek on 15/01/15.
 */

public class MapReduce implements MapDispatcher.MappingDoneInterface, ReduceDispatcher.ReducingDoneInterface {
    Splitter splitter;
    MapDispatcher mapDispatcher;
    ReduceDispatcher reduceDispatcher;
    Grouper grouper;

    @Override
    public void onMapDone(HashMap<String, ArrayList<MappedChunk>> mappedChunks) {
        // Tutaj przekaz reduceDispatcherowi na czym ma pracowac
        // Wywolaj processAll();
    }

    @Override
    public void onReducingDone(HashMap<String, ReducedChunk> keyToReducedChunksMap) {
        // Tutaj przekaz Grouperowi na czym ma pracowac
        // Wywolaj
    }

    public static void main(String[] args) throws IOException {
		// Splitter
        ArrayList<FileChunk> fc = Splitter.calculateChunks("Test/test.txt", 64);
        String outputDirectory = Paths.get(".").toAbsolutePath().normalize().toString();


        // ConnectionHandler - rejestruje node'y
        ConnectionHandler connectionConnectionHandler = ConnectionHandler.getConnectionHandlerInstance();


        // Load Balancer - tworzymy i rejestrujemy w serverze
        LoadBalancer lb = new LoadBalancer();
        connectionConnectionHandler.attachObserver(lb);


//        Node - docelowo będą odpalane niezależnie na zdalnych komputerach
//        try {
//            new Node().registerNode();
//            new Node().registerNode();
//        } catch (NotBoundException e) {
//            e.printStackTrace();
//        }

        try {
            Thread.sleep(15000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // Szybki test dispatchera
        CommandFactory cf = new ExampleFactory();
		MapDispatcher mapDispatcher = new MapDispatcher(fc, lb, cf);
        mapDispatcher.setMappingDoneInterface(mappedChunks -> {
            System.out.println("On map done gets called");

            ReduceDispatcher reduceDispatcher = null;
            try {
                reduceDispatcher = new ReduceDispatcher(mappedChunks, lb, cf);
            } catch (RemoteException e) {
                e.printStackTrace();
            }
            reduceDispatcher.setReducingDoneInterface(new ReduceDispatcher.ReducingDoneInterface() {
                @Override
                public void onReducingDone(HashMap<String, ReducedChunk> keyToReducedChunksMap) {
                    System.out.println("Done Reducing " + keyToReducedChunksMap.size());
                    ArrayList<? extends Chunk> reducedChunks = new ArrayList<>(keyToReducedChunksMap.values());
                    Grouper.groupResultsToFile((ArrayList<Chunk>) reducedChunks, outputDirectory);
                }
            });
            reduceDispatcher.processAll();
        });
		mapDispatcher.processAll();

    }
}
