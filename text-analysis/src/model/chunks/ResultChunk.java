package model.chunks;

import java.net.URL;

/**
 * Created by Filson on 2015-02-23.
 * Klasa do reprezentacji plików będących ostatecznym wynikiem działania programu.
 * Rozszerza klasę Chunk
 * @see Chunk
 */
public class ResultChunk extends Chunk {
    /**
     * Konstruktor klasy ResultChunk
     * @param resultChunkUrl Adres URL pliku.
     */
    public ResultChunk(URL resultChunkUrl) {
        super(resultChunkUrl);
    }
}