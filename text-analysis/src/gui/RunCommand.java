package gui;

import model.chunks.FileChunk;
import model.chunks.MappedChunk;
import model.chunks.ReducedChunk;
import model.commands.interfaces.CommandFactory;
import map_reduce_example.ExampleFactory;
import server.LoadBalancer;
import server.ConnectionHandler;
import server.utils.Splitter;
import server.dispatcher.MapDispatcher;
import server.dispatcher.ReduceDispatcher;
import server.interfaces.ServerObserver;

import java.io.IOException;
import java.io.Serializable;
import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by Michał on 2015-02-24.
 */
public class RunCommand implements Serializable{

    public static LoadBalancer lb=new LoadBalancer();
    private static boolean initialized=false;
    public static void init(ServerObserver reference) throws RemoteException {
        if(!initialized)
        {
            ConnectionHandler.getConnectionHandlerInstance().attachObserver(lb);
            ConnectionHandler.getConnectionHandlerInstance().attachObserver(reference);
            initialized=true;
        }
    }
    public static void exec(String file) throws IOException {

        ArrayList<FileChunk> fc = Splitter.calculateChunks(file, 64);


        // Szybki test dispatchera
        CommandFactory cf = new ExampleFactory();
        MapDispatcher dispatcher = new MapDispatcher(fc, lb, cf);
        dispatcher.setMappingDoneInterface(mappedChunks -> {
            System.out.println("On map done gets called");
            for (Map.Entry<String, ArrayList<MappedChunk>> entry : mappedChunks.entrySet()) {
                System.out.println("Got key " + entry.getKey() + " Size of list: " + entry.getValue().size());
                entry.getValue();
                for (MappedChunk mc : entry.getValue()) {
                    System.out.println("Got chunk " + mc.getChunkUrl());
                }
            }

            ReduceDispatcher reduceDispatcher = null;
            try {
                reduceDispatcher = new ReduceDispatcher(mappedChunks, lb, cf);
            } catch (RemoteException e) {
                e.printStackTrace();
            }
            reduceDispatcher.setReducingDoneInterface(new ReduceDispatcher.ReducingDoneInterface() {
                @Override
                public void onReducingDone(HashMap<String, ReducedChunk> keyToReducedChunksMap) {
                    System.out.println("Done Reducing "+keyToReducedChunksMap.size());
                }
            });
            reduceDispatcher.processAll();
        });
        dispatcher.processAll();
    }
}
