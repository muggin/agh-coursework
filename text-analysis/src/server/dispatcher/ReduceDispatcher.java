package server.dispatcher;

import java.io.Serializable;
import java.rmi.Remote;
import java.util.Map;

import model.commands.interfaces.CommandFactory;
import model.commands.interfaces.Command;
import node.RegisteredNode;
import server.*;
import model.chunks.Chunk;
import model.chunks.MappedChunk;
import model.chunks.ReducedChunk;

import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.HashMap;

/**
 * Created by Olek on 2015-02-23.
 */
public class ReduceDispatcher extends AbstractDispatcher {
    /**
     * Callback definujący zachowanie w przypadku zakończenia jednej operacji reduce.
     */
    private ReduceCommandCallback reduceCommandCallback;

    /**
     * Struktura przechowująca informacje o chunkach które mają być poddane operacji reduce.
     */
    private HashMap<String, ArrayList<MappedChunk>> keyToMappedChunksMap;

    /**
     * Struktura przechowująca informację o zredukowanych chunkach dla danego klucza.
     */
    private static HashMap<String,ReducedChunk> keyToReducedChunksMap;


    /**
     * Callback definijący zachowanie w przypadku zakończenia pracy wszystkich reducerów
     */
    private ReducingDoneInterface reducingDoneInterface;

    /**
     * Interfejs który należy zaimplementować w celu otrzymania powiadomienia o zakończeniu reducowania.
     */
    public interface ReducingDoneInterface extends Serializable{
        public void onReducingDone(HashMap<String,ReducedChunk> keyToReducedChunksMap);
    }

    /**
     * Konstruktor klasy ReduceDispatcher
     * @param mappedChunk Mapa zmapowanych chunków
     * @param lb Load Balancer używany do zlecania zadań
     * @param cf Fabryka komend używana do konstrukcji zleceń
     * @see server.dispatcher.AbstractDispatcher#AbstractDispatcher
     */
    public ReduceDispatcher(HashMap<String, ArrayList<MappedChunk>> mappedChunk, LoadBalancer lb, CommandFactory cf) throws RemoteException {
        super( lb, cf);
        reduceCommandCallback=new ReduceCommandCallback();
        keyToMappedChunksMap=mappedChunk;
        requestToBeDone=mappedChunk.size();
        requestsFinished=0;
        requestsFinished=0;
        keyToReducedChunksMap=new HashMap<>();
    }

    /**
     * Zleca redukcję wszystkich Chunków
     */
    @Override
    public void processAll() {
        for(Map.Entry<String, ArrayList<MappedChunk> > entry:keyToMappedChunksMap.entrySet()){
            processSingle(entry.getValue());
        }
    }

    /**
     * Zleca redukcję pojedyńczej grupy chunków
     * @param singleChunkRequest Lista zredukowanych chunków potrzebnych do stworzenia komendy.
     */
    @Override
    public void processSingle(ArrayList<? extends Chunk> singleChunkRequest) {
        super.processSingle(singleChunkRequest);
        RegisteredNode node=loadBalancer.assignNode();
        Command reduceCommand=commandFactory.createReducer((ArrayList<Chunk>) singleChunkRequest, reduceCommandCallback);
        try {
            node.placeCommand(reduceCommand);
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }

    /**
     * Ustawia ReducingDoneInterface
     * @param reducingDoneInterface
     * @see server.dispatcher.ReduceDispatcher.ReducingDoneInterface
     */
    public void setReducingDoneInterface(ReducingDoneInterface reducingDoneInterface){
        this.reducingDoneInterface=reducingDoneInterface;
    }


    /**
     * Klasa definująca zachowanie w przypadku otrzymania informacji o powodzeniu lub niepowodzeniu komendy.
     */
    private class ReduceCommandCallback extends AbstractDispatcher.DispatcherCallback {

        ReduceCommandCallback() throws RemoteException {
            super();
        }

        @Override
        public void commandCompleted(Chunk oldChunk, ArrayList<Chunk> newChunks) {
            super.commandCompleted(oldChunk, newChunks);
            System.out.println("ReduceCommandCallback: commandCompleted(" + oldChunk + ", " + newChunks + ")");
            ReducedChunk reducedChunk= (ReducedChunk) newChunks.get(0);
            keyToReducedChunksMap.put(reducedChunk.getKey(),reducedChunk);
            if(requestToBeDone==requestsFinished){
                if(reducingDoneInterface!=null){
                    reducingDoneInterface.onReducingDone(keyToReducedChunksMap);
                }
            }
        }

        @Override
        public void commandFailed(Chunk oldChunk) {
            super.commandFailed(oldChunk);
        }
    }
}
