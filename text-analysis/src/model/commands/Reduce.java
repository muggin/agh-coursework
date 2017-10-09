package model.commands;

import model.chunks.Chunk;
import model.chunks.MappedChunk;
import model.chunks.ReducedChunk;
import model.commands.interfaces.Command;
import model.commands.interfaces.CommandCallback;

import java.io.*;
import java.rmi.RemoteException;
import java.util.ArrayList;

/**
 * Created by Wojtek on 17/02/15.
 * Abstrakcyjna klasa na bazie interfejsu Command.
 *
 * Reprezentuje działanie Reducera.
 * Otrzymuje listę obiektów MappedChunk dla wspólnego klucza, będących wynikiem działania Maperów.
 * Składa poszczególne wyniki w jeden.
 *
 * W zależności od potrzeb użytkownika klasa pochodna określa ciało metody processKey() - implementacja wzorca Template Method Pattern.
 *
 * Stworzony na bazie interfejsu Command - implementuje wzorzec Command Pattern.
 *
 * Jest ogólnym produktem fabryki abstrakcyjnej CommandFactory.
 *
 * @see model.commands.interfaces.Command
 * @see model.commands.interfaces.CommandFactory
 * @see model.chunks.Chunk
 * @see model.chunks.FileChunk
 * @see model.chunks.ReducedChunk
 */
public abstract class Reduce implements Command {
    /** Komenda zwrotna dla Reducera */
    CommandCallback commandCallback;
    /** Lista obiektów Chunk (MappedChunk) o wspólnym kluczu */
    protected ArrayList<Chunk> mappedChunks;
    /** Lista wartości odczytanych z plików z mappedChunks */
    protected ArrayList<Long> receivedValues;
    /** Wartość wyniku działania Reducera */
    protected Long finalResult;
    /** Obiekt ReducedChunk dla wyniku działania Reducera */
    protected ReducedChunk reducedChunk;
    /** Klucz, którego dotyczy dany Reducer */
    protected String key;
    /** Scieżka tymczasowego katalogu wyjściowego dla Reducera */
    protected String outputDirectory;

    /**
     * Konstruktor klasy Reduce.
     * @param mappedChunks Lista obiektów Chunk (MappedChunk) będąca zbiorem wyników poszczególnych Mapperów dotyczących jednego klucza.
     * @param commandCallback Komenda zwrotna po przeprowadzeniu działania.
     */
    public Reduce(ArrayList<Chunk> mappedChunks, CommandCallback commandCallback) {
        this.mappedChunks = mappedChunks;
        this.commandCallback = commandCallback;
        this.receivedValues=new ArrayList<>();
    }

    /**
     * Metoda dla głównego celu działania Reducera.
     */
    final public void execute() {
        try {
            readValues();
            processKey();
        } catch (IOException e) {
            e.printStackTrace();
            try {
                commandCallback.commandFailed(mappedChunks.get(0));
            } catch (RemoteException e1) {
                e1.printStackTrace();
            }
        }
    }

    /**
     * Metoda zawierająca konieczne do przeprowadzenia kroki przed właściwym wykonaniem analizy.
     * Ustawia właściwy katalog wyjściowy dla Reducera.
     * @param outputDirectory Scieżka katalogu wyjściowego do modyfikacji.
     */
    public void preExecution(String outputDirectory){
        StringBuilder sb = new StringBuilder(outputDirectory);
        sb.append("/reducer/");
        this.outputDirectory = sb.toString();
        MappedChunk mappedCh = (MappedChunk) mappedChunks.get(0);
        this.key = mappedCh.getKey();
    }

    /**
     * Metoda zawierająca kroki konieczne do przeprowadzenia po metodzie execute().
     * Zapisuje wyliczony wynik do pliku i generuje dla niego obiekt ReducedChunk.
     */
    public void postExecution(){
        File reducedFile = new File(outputDirectory + key + ".reduced");
        BufferedWriter bw = null;
        try {
            if(!reducedFile.exists()){
                reducedFile.createNewFile();
            }
            bw = new BufferedWriter(new FileWriter(reducedFile));
            bw.write(String.valueOf(finalResult));
            bw.close();

            reducedChunk = new ReducedChunk(reducedFile.toURI().toURL(), key);
            ArrayList<Chunk> reducedChunks=new ArrayList<>();
            reducedChunks.add(reducedChunk);
            System.out.println("trying to call reduce cmplete");
            commandCallback.commandCompleted(mappedChunks.get(0), reducedChunks);
        } catch (IOException e) {
            e.printStackTrace();
            try {
                commandCallback.commandFailed(mappedChunks.get(0));
            } catch (RemoteException e1) {
                e1.printStackTrace();
            }
        }
    }

    /**
     * Abstrakcyjna metoda konieczna do nadpisania w klasie pochodnej.
     * Używana w metodzie execute(), zawiera kroki uzależnione od planowanego celu programu.
     * @throws IOException
     */
    public abstract void processKey();

    /**
     * Metoda odczytuje wartości z plików stworzonych przez Mappery i zapisuje je do listy receivedValues.
     * @throws IOException
     */
    private void readValues() throws IOException {
        InputStream is = null;
        BufferedReader br = null;
        String readValue = null;

            for(Chunk ch : mappedChunks){
                is = ch.getChunkUrl().openStream();
                br = new BufferedReader(new InputStreamReader(is));
                readValue = br.readLine();
                try {
                    receivedValues.add(Long.parseLong(readValue));
                }catch (NumberFormatException e){
                    e.printStackTrace();
                    throw new IOException();
                }
            }
    }
}

// Abstract Factory - Product B Interface
// Template Method Pattern - run();
// Command Pattern - Command