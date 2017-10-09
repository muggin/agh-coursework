package model.chunks;

import java.io.Serializable;
import java.net.URL;

/**
 * Created by Wojtek on 20/02/15.
 * Abstrakcyjna klasa reprezentująca plik poprzez jego adres URL.
 */
public abstract class Chunk  implements Serializable {
    protected URL chunkUrl;

    /**
     * Konstruktor klasy Chunk
     * @param chunkUrl Adres URL pliku.
     */
    public Chunk(URL chunkUrl) {
        this.chunkUrl = chunkUrl;
    }

    /**
     * Metoda zwracająca wartość pola chunkURL
     * @return Adres URL pliku.
     */
    public URL getChunkUrl() {
        return chunkUrl;
    }
}
