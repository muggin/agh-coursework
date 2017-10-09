package model.commands.interfaces;

import model.chunks.Chunk;

import java.io.Serializable;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;

/**
 * Created by Wojtek on 19/02/15.
 */
public interface CommandCallback extends Remote, Serializable {
    public static final String LOOKUP_NAME = "MRCommandCallback";

    public void commandCompleted(Chunk oldChunk, ArrayList<Chunk> newChunks) throws RemoteException;
    public void commandFailed(Chunk oldChunk) throws RemoteException;
}
