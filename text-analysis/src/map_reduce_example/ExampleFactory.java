package map_reduce_example;

import model.commands.Map;
import model.commands.Reduce;
import model.commands.interfaces.CommandCallback;
import map_reduce_example.ExampleMap;
import map_reduce_example.ExampleReduce;
import model.chunks.Chunk;
import model.chunks.FileChunk;
import model.commands.interfaces.CommandFactory;

import java.util.ArrayList;

/**
 * Created by Wojtek on 17/02/15.
 */
public class ExampleFactory implements CommandFactory {

    @Override
    public Map createMapper(FileChunk mappedFile, CommandCallback callback) {
        return new ExampleMap(mappedFile, callback);
    }

    @Override
    public Reduce createReducer(ArrayList<Chunk> mappedChunk, CommandCallback callback) {
        return new ExampleReduce(mappedChunk, callback);
    }
}

// Abstract Factory Pattern - Concrete Factory
