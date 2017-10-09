package server.dispatcher;

import model.commands.interfaces.Command;
import model.commands.interfaces.CommandFactory;
import node.RegisteredNode;
import server.LoadBalancer;
import model.chunks.Chunk;
import model.chunks.FileChunk;
import model.chunks.MappedChunk;

import java.io.Serializable;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;

/**
 * Created by Olek on 2015-02-21.
 */
public class MapDispatcher extends AbstractDispatcher {
    /**
     * Struktura przechowująca inforamcję o chunkach należacych do danego klucza.
     */
    private HashMap<String, ArrayList<MappedChunk>> mappedChunks;

    /**
     * Callback definiujący zachowanie w przypadku zakończenia wykonywania komendy.
     */
    private MapCommandCallback mapCommandCallback;

    /**
     * Callback definijący zachowanie w przypadku zakończenia pracy wszystkich mapperów
     */
    private MappingDoneInterface mappingDoneInterface;

    /**
     * Lista chunków które mają być zmapowane
     */
    private ArrayList<FileChunk> chunkToMap;

    /**
     * Interfejs który należy zaimplementować w celu otrzymania powiadomienia o zakończeniu mapowania.
     */
    public interface MappingDoneInterface extends Serializable {
        public void onMapDone(HashMap<String, ArrayList<MappedChunk>> mappedChunks);
    }

    /**
     * Konstrukor Map Dispatchera
     * @param fc Lista Chunków którę mają być zmapowane
     * @param lb Load Balancer używany do zlecania zadań
     * @param cf Fabryka komend używana do konstrukcji zleceń
     * @see server.dispatcher.AbstractDispatcher#AbstractDispatcher
     */
    public MapDispatcher(ArrayList<FileChunk> fc, LoadBalancer lb, CommandFactory cf) throws RemoteException {
        super( lb, cf);
        mappedChunks=new HashMap<>();
        requestToBeDone=fc.size();
        requestsFinished=0;
        requestsInProgress=0;
        chunkToMap=fc;
        mapCommandCallback=new MapCommandCallback();
    }


    /**
     * Zleca Mapowanie wszystkich Chunków
     */
    @Override
    public void processAll() {
        for(FileChunk fileChunk : chunkToMap) {
            processSingle(new ArrayList<FileChunk>() {{ add(fileChunk); }});
        }
    }

    /**
     * Zleca mapowanie pojedyńczego chunka
     * @param fileChunks Jednoelementowa lista zawierająca pojedyńczy Chunk
     */
    @Override
    public void processSingle(ArrayList<? extends Chunk> fileChunks) {
        super.processSingle(fileChunks);
        System.out.println("Dispatcher: processSingle(" + fileChunks.get(0) + ")");
        RegisteredNode node = loadBalancer.assignNode();
        Command command = commandFactory.createMapper((FileChunk) fileChunks.get(0), mapCommandCallback);
        try {
            node.placeCommand(command);
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }

    /**
     * Ustawia MappingDoneInterface
     * @param mappingDoneInterface callback
     * @see server.dispatcher.MapDispatcher.MappingDoneInterface
     */
    public void setMappingDoneInterface(MappingDoneInterface mappingDoneInterface) {
        this.mappingDoneInterface=mappingDoneInterface;
    }

    /**
     * Klasa definjująca zachowanie w przypadku otrzymania informacji o powodzeniu lub niepowodzeniu pojedyńczego mapowania.
     */
    private class MapCommandCallback extends AbstractDispatcher.DispatcherCallback {

        MapCommandCallback() throws RemoteException {
            super();
        }

        @Override
        public void commandCompleted(Chunk oldChunk, ArrayList<Chunk> newChunks) {
            super.commandCompleted(oldChunk, newChunks);

            System.out.println("MapCommandCallback: commandCompleted(" + oldChunk + ", " + newChunks + ")");
            for(Chunk chunk:newChunks){
                MappedChunk mappedChunk=(MappedChunk) chunk;
                if(mappedChunks.get(mappedChunk.getKey())==null){
                    mappedChunks.put(mappedChunk.getKey(),new ArrayList<>());
                }
                mappedChunks.get(mappedChunk.getKey()).add(mappedChunk);
            }
            if(requestToBeDone==requestsFinished && mappingDoneInterface!=null){
                mappingDoneInterface.onMapDone(mappedChunks);
            }
        }
    }
}