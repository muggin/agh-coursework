package model.chunks;

import java.net.URL;

/**
 * Created by Wojtek on 20/02/15.
 * Klasa do reprezentacji plików będących wynikiem działania Reducera.
 * Rozszerza klasę Chunk
 * @see Chunk
 * @see model.commands.Reduce
 */
public class ReducedChunk extends Chunk {
    /** Wartość klucza, którego dotyczy wynik Reducera */
    private String key;

    /**
     * Konstruktor klasy ReducedChunk
     * @param reducedChunkUrl Adres URL pliku.
     */
    public ReducedChunk(URL reducedChunkUrl, String key) {
        super(reducedChunkUrl);
        this.key = key;
    }

    /**
     * Metoda zwracająca wartość klucza.
     * @return Wartość key.
     */
    public String getKey() {
        return key;
    }
}
