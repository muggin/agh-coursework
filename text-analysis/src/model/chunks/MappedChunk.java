package model.chunks;

import java.net.URL;

/**
 * Created by Wojtek on 20/02/15.
 * Klasa do reprezentacji plików będących wynikiem działania Mappera.
 * Rozszerza klasę Chunk
 * @see Chunk
 * @see model.commands.Map
 */
public class MappedChunk extends Chunk {
    /** Wartość klucza, wg którego rozróżniane są wyniki Mapera */
    private String key;

    /**
     * Konstruktor klasy MappedChunk.
     * @param mappedChunkUrl Adres URL do pliku.
     * @param key Wartość klucza
     */
    public MappedChunk(URL mappedChunkUrl, String key) {
        super(mappedChunkUrl);
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
