package EntryPackage;

import java.io.Serializable;

public class Entry implements Serializable {
	
	private static final long serialVersionUID = -517294758762658303L;
	private String word;
	private String clue;
	
	/**
	 * 
	 * @param word
	 * @param clue
	 */
	public Entry (String word, String clue)
	{
		this.word = word;
		this.clue = clue;
	}
	
	/**
	 * 
	 * @return
	 */
	public String getWord ()
	{
		return word;
	}
	
	/**
	 * 
	 * @return
	 */
	public String getClue ()
	{
		return clue;
	}
	
	/**
	 * 
	 */
	public String toString()
	{
		return String.format("%s - %s\n", word, clue);
	}
}
