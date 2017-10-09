package BoardPackage;

import java.io.Serializable;
import java.util.BitSet;

public class BoardCell implements Serializable {
	private static final long serialVersionUID = -463465845464428253L;
	private String content;
	private String solution;
	private BitSet horizontal;
	private BitSet vertical;
	private int x;
	private int y;
	
	/*
	 * METODY DO SPRAWDZANIA CZY KOMORKA MOZE BYC POCZATKIEM/KONCEM HASLA
	 */
	
	public BoardCell (int x, int y)
	{
		this.content = null;
		this.solution = null;
		this.horizontal = new BitSet(4);
		horizontal.set(1, 3);
		this.vertical = new BitSet(4);
		vertical.set(1,3);
		this.x = x;
		this.y = y;
	}
	
	public BoardCell (int x, int y, String content, String solution)
	{
		this.content = content;
		this.solution = solution;
		this.horizontal = new BitSet(4);
		this.vertical = new BitSet(4);
		this.horizontal.set(1,3);
		this.vertical.set(1,3);
		this.x = x;
		this.y = y;
	}
	
	public BoardCell (int x, int y, String content, String solution, BitSet horizontal, BitSet vertical)
	{
		this.content = content;
		this.solution = solution;
		this.horizontal = horizontal;
		this.vertical = vertical;
		this.x = x;
		this.y = y;
	}
	
	/**
	 * Funkcja zwraca wartosc pola solution.
	 * @return wartosc pola solution.
	 */
	public String getContent()
	{
		return content;
	}
	
	/**
	 * 
	 * @return
	 */
	public BitSet getHorizontal() 
	{
		return horizontal;
	}
	
	/**
	 * Funkcja zwraca wartosc pola solution.
	 * @return wartosc pola solution.
	 */
	public String getSolution()
	{
		return solution;
	}
	
	/**
	 * 
	 * @return
	 */
	public BitSet getVertical() 
	{
		return vertical;
	}
	
	/**
	 * 
	 * @return
	 */
	public int getX()
	{
		return this.x;
	}

	/**
	 * 
	 * @return
	 */
	public int getY()
	{
		return this.y;
	}

	/**
	 * Funkcja ustawia wartosc pola content.
	 * @param content - nowa wartosc pola content.
	 */
	public void setContent (String content)
	{
		this.content = content;
	}

	/**
	 * 
	 * @param horizontal
	 */
	public void setHorizontal(BitSet horizontal) 
	{
		this.horizontal.and(horizontal);
	}
	
	public void setSolution (String solution)
	{
		this.solution = solution;
	}
	
	/**
	 * 
	 * @param vertical
	 */
	public void setVertical(BitSet vertical) 
	{
		this.vertical.and(vertical);
	}
	
	public boolean isEmpty()
	{
		if (content == null)
			return true;
		else
			return false;
	}
	
	/**
	 * Funkcja zamienia obiekt klasy BoardCell na String.
	 */
	@Override
	public String toString()
	{
		return content;
	}
}
