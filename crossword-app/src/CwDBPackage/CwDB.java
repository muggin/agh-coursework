package CwDBPackage;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Serializable;
import java.util.LinkedList;

import EntryPackage.Entry;

public class CwDB implements Serializable {
	private static final long serialVersionUID = -1263795962875415235L;
	protected LinkedList<Entry> dict;
	
	public CwDB (String filename)
			throws FileNotFoundException, IOException
	{
		dict = new LinkedList<Entry>();
		createDB(filename);
	}
	
	/**
	 * Funkcja wstawia nowy obiekt do bazy danych.
	 * @param word - slowo wstawiane do bazy danych
	 * @param clue - odpowiadajaca podpowiedz wstawiana do bazy danych
	 */
	public void add (String word, String clue)
	{
		dict.add(new Entry(word, clue));
	}
	
	/**
	 * Funkcja wyszukuje w bazie danych obiekt zawierajacy podane slowo.
	 * @param word - slowo wyszukiwane w bazie danych.
	 * @return obiekt zawierajacy podane slowo.
	 */
	public Entry get (String word)
	{
		for(Entry entry : dict)
		{
			if (entry.getWord().equals(word))
				return entry;
		}
		return null;
	}
	
	/**
	 * Funkcja usuwa z bazy danych obiekt zawierdajacy podane slowo.
	 * @param word - slowo wyszukiwane w bazie danych.
	 */
	public void remove (String word)
	{
		for(Entry entry : dict)
		{
			if (entry.getWord().equals(word))
			{
				dict.remove(entry);
				break;
			}
		}
	}
	
	/**
	 * Funkcja zapisuje baze danych do podanego pliku.
	 * @param filename - nazwa pliku do ktorego ma byc zapisana baza danych.
	 */
	public void saveDB (String filename)
			throws FileNotFoundException, IOException
	{
		BufferedWriter bw = outputFile(filename);
		
		for(Entry entry : dict)
		{
			bw.write(entry.getWord());
			bw.newLine();
			bw.write(entry.getClue());
			bw.newLine();
			bw.flush();
		}
	}
	
	/**
	 * Funkcja pokazuje rozmiar bazy danych.
	 * @return - rozmiar listy dict (bazy danych).
	 */
	public int getSize()
	{
		return dict.size();
	}
	
	/**
	 * Funkcja tworzy nowa baze danych na podstawie pliku tekstowego.
	 * @param filename
	 * @throws FileNotFoundException
	 * @throws IOException
	 */
	protected void createDB (String filename) 
			throws FileNotFoundException, IOException
	{
		BufferedReader br = inputFile(filename);
		String inputWord, inputClue;
		
		while ((inputWord = br.readLine()) != null && (inputClue = br.readLine()) != null)
		{
			add(inputWord, inputClue);
		}
		closeFile(br);
	}
	
	/**
	 * 
	 * @param filename
	 * @return
	 * @throws FileNotFoundException
	 * @throws IOException
	 */
	private BufferedReader inputFile(String filename) 
			throws FileNotFoundException, IOException
	{
		BufferedReader br = null;
		try
		{
			br = new BufferedReader(new InputStreamReader(new FileInputStream(filename), "UTF8"));
		}
		catch (FileNotFoundException e1)
		{
			System.out.println("Nie znaleziono wskazanego pliku.");
		}
		catch (IOException e2)
		{
			System.out.println("Blad przy otwieraniu pliku.");
		}
		return br;
	}
	
	/**
	 * 
	 * @param filename
	 * @return
	 * @throws FileNotFoundException
	 * @throws IOException
	 */
	private BufferedWriter outputFile(String filename) 
			throws FileNotFoundException, IOException
	{
		BufferedWriter bw = null;
		try
		{
			bw = new BufferedWriter(new FileWriter(filename));
		}
		catch (FileNotFoundException e1)
		{
			System.out.println("Nie znaleziono wskazanego pliku.");
		}
		catch (IOException e2)
		{
			System.out.println("Blad przy otwieraniu pliku.");
		}
		return bw;
	}
	
	/**
	 * 
	 * @param bw
	 * @throws IOException
	 */
	private void closeFile (BufferedReader bw)
			throws IOException
	{
		try
		{
			bw.close();
		}
		catch (IOException e1)
		{
			System.out.println("Blad przy zamykaniu pliku.");
		}
	}
}
