package model.chunks;

import java.net.URL;

/**
 * Created by Wojtek on 18/02/15.
 * Klasa określająca fragment pliku rozszerzająca klasę Chunk.
 * @see Chunk
 */

public class FileChunk extends Chunk {
    /** Wartość przesunięcia względem początku pliku. Początek danego fragmentu. */
    private long offset;
    /** Rozmar danego fragmentu wyrażony w Bajtach. */
    private long chunkSize;

    /**
     * Konstruktor klasy FileChunk
     * @param fileUrl Adres URL pliku.
     * @param offset Wartość przesunięcia względem początku pliku.
     * @param chunkSize Rozmiar danego fragmentu.
     */
    public FileChunk(URL fileUrl, long offset, long chunkSize) {
        super(fileUrl);
        this.offset = offset;
        this.chunkSize = chunkSize;
    }

    /**
     * Metoda zwracająca wartość przesunięcia względem początku pliku.
     * @return Wartość offset.
     */
    public long getOffset() {
        return offset;
    }

    /**
     * Metoda zwracająca rozmiar danego fragmentu.
     * @return Wartość chunkSize.
     */
    public long getChunkSize() {
        return chunkSize;
    }
}
