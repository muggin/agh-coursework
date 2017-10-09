package map_reduce_example;

import model.commands.interfaces.CommandCallback;
import model.commands.Reduce;
import model.chunks.Chunk;

import java.util.ArrayList;

/**
 * Created by Wojtek on 17/02/15.
 * Klasa będąca konkretnym produktem fabryki abstrakcyjnej CommandFactory.
 * Reprezentuje właściwy obiekt Reducera, którego działanie uzależnione jest od ciała metody processKey()
 *
 * Sumuje poszczególne wartości wynikowe wygenerowane przez Mapperów, które dotyczą jednego (wspólnego) klucza.
 *
 * @see model.commands.Reduce
 * @see model.commands.interfaces.CommandFactory
 */
public class ExampleReduce extends Reduce {

    /**
     * Konstruktor klasy ExampleReduce
     * @see model.commands.Reduce#Reduce(java.util.ArrayList, model.commands.interfaces.CommandCallback)
     */
    public ExampleReduce(ArrayList<Chunk> mappedChunks, CommandCallback commandCallback) {
        super(mappedChunks, commandCallback);
    }

    @Override
    /**
     * Sumuje wartości z listy receivedValues, a wynik zapisuje w finalResult.
     * @see model.commands.Reduce#processKey()
     */
    public void processKey() {
        System.out.println("ExampleReduce: processKey()");
        finalResult = 0L;
        for(Long value : receivedValues){
            finalResult += value;
        }

        System.out.println("Final result "+finalResult);
    }
}

// Abstract Factory - Concrete Product B