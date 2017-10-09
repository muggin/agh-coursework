package map_reduce_example;

import model.commands.Map;
import model.commands.interfaces.CommandCallback;
import model.chunks.FileChunk;

import java.io.*;

/**
 * Created by Wojtek on 17/02/15.
 * Klasa będąca konkretnym produktem fabryki abstrakcyjnej CommandFactory.
 * Reprezentuje właściwy obiekt Mappera, którego działanie uzależnione jest od ciała metody processSegment()
 *
 * Analizuje zadany fragment i zlicza ilość słów w tym fragmencie.
 *
 * @see model.commands.Map
 * @see model.commands.interfaces.CommandFactory
 */
public class ExampleMap extends Map {
    /**
     * Konstruktor klasy ExampleMap
     * @see model.commands.Map#Map(model.chunks.FileChunk, model.commands.interfaces.CommandCallback)
     */
    public ExampleMap(FileChunk mappedFile, CommandCallback commandCallback) {
        super(mappedFile, commandCallback);
    }

    @Override
    /**
     * Analizuje właściwy fragment pliku i dla każdego napotkanego słowa
     * emituje klucz "WordCount" poprzez metodę emit(key).
     *
     * @see model.commands.Map#processChunk()
     * @see Map#emit(String)
     */
    public void processChunk() throws IOException {
        System.out.println("ExampleMap: processChunk()");
        Boolean isWord = false;
        RandomAccessFile raf = new RandomAccessFile(fileToMapPath, "r");
        int ch;
        try {
            while(raf.getFilePointer() < raf.length()) {
                ch = raf.readByte();
                if(Character.isLetterOrDigit(ch) && !isWord){
                    emit("WordCount");
                    isWord = true;
                }else if(!Character.isLetterOrDigit(ch) && isWord){
                    isWord = false;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            raf.close();
        }
    }
}

// Abstract Factory - Concrete Product A