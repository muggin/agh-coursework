package EntryPackage;

import java.io.Serializable;

public class CwEntry extends Entry implements Serializable {

	private static final long serialVersionUID = 8404746978827748412L;
	public enum Direction {HORIZ, VERT};
	
	private int x;
	private int y;
	private Direction d;
	
	public CwEntry(String word, String clue, int x, int y, Direction d)
	{
		super(word, clue);
		this.x = x;
		this.y = y;
		this.d = d;
	}
	
	/**
	 * 
	 * @return
	 */
	public int getX() 
	{
		return x;
	}
	
	/**
	 * 
	 * @return
	 */
	public int getY() 
	{
		return y;
	}
	
	/**
	 * 
	 * @return
	 */
	public Direction getD() 
	{
		return d;
	}
}
