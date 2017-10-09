package CwDBPackage;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.LinkedList;
import java.util.Random;

import EntryPackage.Entry;

public class InteliCwDB extends CwDB {
	
	private static final long serialVersionUID = 2308949937491440017L;
	public InteliCwDB (String filename)
			throws FileNotFoundException, IOException
	{
		super(filename);
	}
	
	
	/**
	 * Funkcja wstawia nowy obiekt do bazy danych w determinowane przez porzadek alfabetyczny miejsce. 
	 * @param word - slowo wstawiane do bazy danych
	 * @param clue - odpowiadajaca podpowiedz wstawiana do bazy danych
	 */
	@Override
	public void add (String word, String clue)
	{
		dict.add(new Entry(word, clue));
	}
	
	/**
	 * Funkcja wybiera z bazy danych hasla ktore pasuja do podanego wzorca.
	 * @param pattern - wzorzec hasla.
	 * @return Lista obiektow Entry ktore pasuja do podanego wzorca
	 */
	public LinkedList<Entry> findAll (String pattern)
	{
		LinkedList<Entry> results = new LinkedList<Entry>();
		
		for (Entry entry : dict)
		{
			if (entry.getWord().matches(pattern))
				results.add(entry);
		}
		
		return results;
	}
	
	/**
	 * Funkcja wybiera losowy element bazy danych.
	 * @return losowo wybrany element bazy danych.
	 */
	public Entry getRandom ()
	{
		int randomIndex = new Random().nextInt(dict.size());
		return dict.get(randomIndex);
	}
	
	/**
	 * Funkcja wybiera losowy element bazy danych o wybranej dlugosci.
	 * @param length - dlugosc szukanego slowa.
	 * @return losowo wybrany element bazy danych o wybranej dlogosci.
	 */
	public Entry getRandom (int length)
	{
		LinkedList<Entry> results = findAll("\\w{" + length + "}");
		if (results.size() > 0)
		{
			int randomIndex = new Random().nextInt(results.size());
			return results.get(randomIndex);
		}
		else
			return null;
	}
	
	/**
	 * Funkcja wybiera losowy element bazy danych o wybranej dlugosci.
	 * @param minLength - minimalna dlugosc szukanego slowa.
	 * @param maxLength - maksymalna dlugosc szukanego slowa.
	 * @return losowo wybrany element bazy danych o wybranej dlugosci.
	 */
	public Entry getRandom (int minLength, int maxLength)
	{
		LinkedList<Entry> results = findAll("\\w{" + minLength + "," + maxLength + "}");
		if (results.size() > 0)
		{
			int randomIndex = new Random().nextInt(results.size());
			return results.get(randomIndex);
		}
		else
			return null;
	}
	
	/**
	 * Funkcja wybiera losowy element bazy danych pasujacy do podanego wzorca.
	 * @param pattern - wzorzec wyszukiwanego hasla.
	 * @return losowo wybrany element bazy danych pasujacy do podanego wzorca.
	 */
	public Entry getRandom (String pattern)
	{
		LinkedList<Entry> results = findAll(pattern);
		if (results.size() > 0)
		{
			int randomIndex = new Random().nextInt(results.size());
			return results.get(randomIndex);
		}
		else
			return null;
	}
}
