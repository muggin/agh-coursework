package model.commands.interfaces;

import model.chunks.Chunk;
import model.chunks.FileChunk;

import java.io.Serializable;
import java.util.ArrayList;

/**
 * Created by Wojtek on 17/02/15.
 * Interfejs będący fabryką obiektów typu Command.
 */
public interface CommandFactory extends Serializable {
    /**
     * Tworzy Command dla Mappera.
     * @param mappedFile Obiekt FileChunk określający fragment pliku wejściowego dla Mappera.
     * @param callback Komenda zwrotna do uruchomienia po zakończeniu działania.
     * @return Obiekt typu Command
     */
    public Command createMapper(FileChunk mappedFile, CommandCallback callback);
    public Command createReducer(ArrayList<Chunk> mappedChunk, CommandCallback callback);
}

// Abstract Factory Pattern - Abstract Factory Interface