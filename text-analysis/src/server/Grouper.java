package server;

import model.chunks.Chunk;
import model.chunks.ReducedChunk;
import model.chunks.ResultChunk;

import java.io.*;
import java.util.ArrayList;

/**
 * Created by Filson on 2015-02-23.
 *
 * Klasa abstrakcyjna odpowiedzialna za łączenie wyników działania poszczególnych klientów zdalnych
 * w jeden plik wynikowy programu.
 *
 */
public abstract class Grouper {
    /**
     * Metoda grupująca pojedyncze wyniki w jednym pliku wynikowym. Odczytuje
     * pliki wygenerowane przez Reducery i zapisuje dane wartości w pliku
     * wyjściowym z określeniem odpowiadających kluczy.
     *
     * @param reducedChunks Lista obiektów Chunk (ReducedChunk) odnoszących się do plików wynikowych wszystkich Reducerów.
     * @param resultLocation Lokalizacja, w której ma zostać zapisany plik wyjściowy.
     * @return Obiekt ResultChunk odnoszący się do wyjściowego pliku z ostatecznym wynikiem działania programu.
     */
    public static ResultChunk groupResultsToFile(ArrayList<Chunk> reducedChunks, String resultLocation){
        File resultFile = new File(resultLocation + "/MapReduceResult.txt");
        int b = 0;
        ResultChunk result = null;
        try {
            if(!resultFile.exists())
                resultFile.createNewFile();

            BufferedWriter bw = new BufferedWriter(new FileWriter(resultFile));

            for(Chunk chunk : reducedChunks){
                InputStream is = chunk.getChunkUrl().openStream();

                bw.write(((ReducedChunk) chunk).getKey() + " ");

                while((b = is.read()) != -1 ){
                    bw.write((char)b);
                }
                bw.write("\n");
                is.close();
            }
            bw.close();
            result = new ResultChunk(resultFile.toURI().toURL());
        } catch (IOException e) {
            e.printStackTrace();
        }
        return result;
    }
}
