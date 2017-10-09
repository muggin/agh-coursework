package model.commands;

import model.chunks.Chunk;
import model.chunks.FileChunk;
import model.chunks.MappedChunk;
import model.commands.interfaces.Command;
import model.commands.interfaces.CommandCallback;

import java.io.*;
import java.rmi.RemoteException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;

/**
 * Created by Wojtek on 17/02/15.
 * Abstrakcyjna klasa na bazie interfejsu Command.
 *
 * Reprezentuje działanie Mapera.
 * Na podstawie otrzymanego obiektu FileChunk odczytuje odpowiedni fragment
 * pliku i przeprowadza jego analizę. Wyniki segreguje względem zadanych kluczy.
 *
 * W zależności od potrzeb użytkownika klasa pochodna określa ciało metody processSegment() - implementacja wzorca Template Method Pattern.
 *
 * Stworzony na bazie interfejsu Command - implementuje wzorzec Command Pattern.
 *
 * Jest ogólnym produktem fabryki abstrakcyjnej CommandFactory.
 *
 * @see model.commands.interfaces.Command
 * @see model.commands.interfaces.CommandFactory
 * @see model.chunks.Chunk
 * @see model.chunks.FileChunk
 * @see model.chunks.MappedChunk
 */
public abstract class Map implements Command {
    /** Mapa  łącząca wynik z wartością klucza. */
    protected HashMap<String, Long> mappedValues = new HashMap<>();
    /** Komenda zwrotna będąca odpowiedzią na przeprowadzone działania. */
    protected CommandCallback commandCallback;
    /** FileChunk określający fragment do analizy. */
    protected FileChunk mappedFile;
    /** Scieżka do pliku zawierającego właściwy fragment do analizy. */
    protected String fileToMapPath;
    /** Lista obiektów Chunk (MappedChunk) wskazujących na wyniki działania klasy. */
    protected ArrayList<Chunk> mappedChunks;
    /** Scieżka tymczasowego katalogu wyjściowego dla Mappera */
    protected String outputDirectory;

    /**
     * Konstruktor klasy Map
     * @param mappedFile Obiekt FileChunk określający fragment pliku do analizy.
     * @param commandCallback Komenda zwrotna po przeprowadzeniu działania.
     */
    public Map(FileChunk mappedFile, CommandCallback commandCallback) {
        this.mappedFile = mappedFile;
        this.commandCallback = commandCallback;
        this.mappedChunks = new ArrayList<>();
    }

    /**
     * Metoda przeprowadzająca analizę fragmentu.
     * Bazuje na metodzie processSegment().
     */
    final public void execute() {
        try (InputStream is = mappedFile.getChunkUrl().openStream()) {
            prepareFileToMap(is, mappedFile.getChunkSize());
            processChunk();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Metoda zawierająca konieczne do przeprowadzenia kroki przed właściwym wykonaniem analizy.
     * Ustawia właściwy katalog wyjściowy dla Mappera.
     * @param outputDirectory Scieżka katalogu wyjściowego do modyfikacji.
     */
    public void preExecution(String outputDirectory) {
        StringBuilder sb = new StringBuilder(outputDirectory);
        sb.append("/mapper/");
        this.outputDirectory = sb.toString();
    }

    /**
     * Metoda zawierająca kroki konieczne do przeprowadzenia po właściwej analizie.
     * Usuwa tymczasowy plik zawierający właściwy fragment do analizy.
     * Na podstawie mapy mappedValues generuje pliki wyjściowe oraz listę wskazujących na nie obiektów MappedChunk.
     */
    public void postExecution() {
        File toDelete = new File(fileToMapPath);
        if(toDelete.exists())
            toDelete.delete();

        for (String key : mappedValues.keySet()) {
            try {
                File chunkFile = new File(outputDirectory + key+ hashCode() + ".chunk");

                if (!chunkFile.exists()) {
                    chunkFile.createNewFile();
                }

                BufferedWriter bw = new BufferedWriter(new FileWriter(chunkFile));
                bw.write(mappedValues.get(key).toString());
                bw.close();

                mappedChunks.add(new MappedChunk(chunkFile.toURI().toURL(), key));

            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        try {
            commandCallback.commandCompleted(mappedFile, mappedChunks);
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }

    /**
     * Abstrakcyjna metoda konieczna do nadpisania w klasie pochodnej.
     * Używana w metodzie execute(), zawiera kroki uzależnione od planowanego celu programu.
     * @throws IOException
     */
    public abstract void processChunk() throws IOException;

    /**
     * Dla określonej wartości klucza, zwiększa licznik wystąpień tego klucza w mapie mappedValues.
     * @param key Wartość klucza mapy.
     */
    public void emit(String key) {
        Long value = mappedValues.get(key);
        if (value == null) {
            mappedValues.put(key, 1L);
        } else {
            mappedValues.put(key, value + 1L);
        }
    }

    /**
     * Przygotowuje źródło wejściowe do wyłuskania odpowiedniego fragmentu.
     * @param is Obiekt InputStream dla pliku wejściowego.
     * @param offset Wartość przesunięcia względem początku pliku.
     * @throws IOException
     */
    private void prepareStream(InputStream is, long offset) throws IOException {
        long skipped = 0;
        long offsetRemaining = offset;
        do {
            skipped = is.skip(offsetRemaining);
            offsetRemaining -= skipped;
        } while (offsetRemaining != 0);
    }

    /**
     * Tworzy plik zawierający odpowiedni fragment z pliku wejściowego.
     * @param is Obiekt InputStream dla pliku wejściowego.
     * @param partLength Długość fragmentu do analizy wyrażona w Bajtach.
     * @throws IOException
     */
    private void prepareFileToMap(InputStream is, long partLength) throws IOException {
        Date dNow = new Date( );
        SimpleDateFormat ft = new SimpleDateFormat ("hh_mm_ss_SS");
        fileToMapPath = outputDirectory + ft.format(dNow) +".tmp";
        RandomAccessFile fileToMap = new RandomAccessFile(fileToMapPath, "rw");

        prepareStream(is, mappedFile.getOffset());
        do{
            fileToMap.writeByte(is.read());
        }while (fileToMap.getFilePointer() < mappedFile.getChunkSize());
        fileToMap.close();
    }
}

// Abstract Factory Pattern - Product A Interface
// Template Method Pattern - run();
// Command Pattern - Command