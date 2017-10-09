package server.utils;

import model.chunks.FileChunk;

import java.io.*;
import java.net.URL;
import java.util.ArrayList;

/**
 * Abstrakcyjna klasa służąca do podziału pliku wejściowego na fragmenty.
 */
public abstract class Splitter {
    /**
     * Generuje FileChunk dla każdego z fragmentów pliku wejściowego.
     * @see model.chunks.FileChunk
     * @param inputFilePath Scieżka do pliku wejściowego.
     * @param chunkSizeKB Rozmiar pojedynczej części pliku wejściowego (wyrażony w KB).
     * @return Lista obiektów typu FileChunk określających poszczególne części pliku wejściowego.
     * @throws IOException
     */
    public static ArrayList<FileChunk> calculateChunks(String inputFilePath, int chunkSizeKB) throws IOException {
        long totalOffset = 0L;
        File inputFile = new File(inputFilePath);
        URL inputFileUrl = inputFile.toURI().toURL();
        long partSize = chunkSizeKB * 1024;
        ArrayList<FileChunk> fileChunks = new ArrayList<>();
        ArrayList<Long> splitPoints;

        splitPoints = findSplitPoints(inputFile, partSize);
           for (long chunkSize : splitPoints){
               fileChunks.add(new FileChunk(inputFileUrl, totalOffset, chunkSize - totalOffset));
               totalOffset += (chunkSize - totalOffset);
           }
        return fileChunks;
    }

    /**
     * Wyznacza punkty podziału pliku wejściowego.
     * @param inputFile Reprezentacja pliku wejściowego.
     * @param partSize Rozmiar pojedynczej części pliku wejściowego (wyrażony w Bajtach).
     * @return Lista wartości określających punkty podziału.
     * @throws FileNotFoundException Plik wejściowy nie istnieje.
     */
	private static ArrayList<Long> findSplitPoints(File inputFile, long partSize) throws FileNotFoundException{
		long startPos = 0;
        long endPos = partSize;
        long inputFileSize = inputFile.length();
        ArrayList<Long> splitPoints = new ArrayList<>();
    	try {
	        RandomAccessFile raf = new RandomAccessFile(inputFile, "r");
            while(raf.getFilePointer() < inputFileSize){
	          	raf.seek(endPos);
	           	if(endPos < inputFileSize){
	           		while( Character.isLetterOrDigit(raf.readByte()) );
	           	}
	           	endPos = raf.getFilePointer();
	           	splitPoints.add(endPos);

		        startPos = endPos;
		        endPos = startPos + partSize;
		        if(endPos > inputFileSize) endPos = inputFileSize;
	        }
	        raf.close();
	    } catch (IOException e) {
	        System.out.println("IOException:");
	        e.printStackTrace();
	    }
		return splitPoints;
	}
}
