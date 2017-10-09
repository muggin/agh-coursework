package ModelPackage;
import java.awt.Dimension;
import java.io.Serializable;
import java.util.Collections;
import java.util.Date;
import java.util.Iterator;
import java.util.LinkedList;

import BoardPackage.Board;
import BoardPackage.BoardCell;
import CwDBPackage.InteliCwDB;
import EntryPackage.CwEntry;
import StrategyPackage.Strategy;

public class Crossword implements Serializable {
	private static final long serialVersionUID = -7228721268321161957L;
	private final long CID;
	private LinkedList<CwEntry> entries;
	private Board gameBoard;
	private InteliCwDB cwdb;
	
	public Crossword(InteliCwDB cwdb, long ID, int height, int width)
	{
		CID = getUniqueID();
		this.cwdb = cwdb;
		this.entries = new LinkedList<CwEntry>();
		this.gameBoard = new Board(height, width);
	}
	
	/**
	 * 
	 * @return
	 */
	public LinkedList<Boolean> checkBoardSolution()
	{
		LinkedList<Boolean> result = new LinkedList<Boolean>();
		for (int h = 0; h < gameBoard.getHeight(); h++)
		{
			for (int w = 0; w < gameBoard.getWidth(); w++)
			{
				if (gameBoard.checkCell(h, w))
				{
					BoardCell cell = gameBoard.getCell(h,w);
					
					if (cell.getContent().toLowerCase().equals(cell.getSolution().toLowerCase()))
						result.add(true);
					else
						result.add(false);
				}
			}
		}
		return result;
	}
	
	/**
	 * 
	 * @param boardState
	 */
	public void setBoardSolution(LinkedList<String> boardState)
	{
		for (int h = 0; h < gameBoard.getHeight(); h++)
		{
			for (int w = 0; w < gameBoard.getWidth(); w++)
			{
				if (gameBoard.checkCell(h, w))
					gameBoard.getCell(h,w).setSolution(boardState.pop());
			}
		}
	}
	
	/**
	 * 
	 * @return
	 */
	public LinkedList<String> getBoardSolution()
	{
		LinkedList<String> result = new LinkedList<String>();
		for (int h = 0; h < gameBoard.getHeight(); h++)
		{
			for (int w = 0; w < gameBoard.getWidth(); w++)
			{
				if (gameBoard.checkCell(h, w))
					result.add(gameBoard.getCell(h, w).getSolution());
			}
		}
		return result;
	}
	
	/**
	 * 
	 * @return
	 */
	public LinkedList<String> getBoardContent()
	{
		LinkedList<String> result = new LinkedList<String>();
		for (int h = 0; h < gameBoard.getHeight(); h++)
		{
			for (int w = 0; w < gameBoard.getWidth(); w++)
			{
				if (gameBoard.checkCell(h, w))
					result.add(gameBoard.getCell(h, w).getContent());
			}
		}
		return result;
	}
	
	/**
	 * 
	 * @return
	 */
	public LinkedList<Boolean> getBoardStatus()
	{
		LinkedList<Boolean> result = new LinkedList<Boolean>();
		for (int h = 0; h < gameBoard.getHeight(); h++)
		{
			for (int w = 0; w < gameBoard.getWidth(); w++)
			{
				if (gameBoard.checkCell(h, w))
					result.add(true);
				else
					result.add(false);
			}
		}
		return result;
	}
	
	/**
	 * 
	 * @return
	 */
	public Dimension cwDimension()
	{
		if (gameBoard != null)
			return new Dimension(gameBoard.getWidth(), gameBoard.getHeight());
		else
			return new Dimension(0, 0);
	}
	
	/**
	 * 
	 * @return
	 */
	public Iterator<CwEntry> getROEntryIter()
	{
		return Collections.unmodifiableList(entries).listIterator();
	}
	
	/**
	 * 
	 * @return
	 */
	public Board getBoardCopy()
	{
		if (this.gameBoard != null)
			return new Board(this.gameBoard);
		else
			return null;
	}
	
	/**
	 * 
	 * @return
	 */
	public InteliCwDB getCwDB()
	{
		return cwdb;
	}
	
	/**
	 * 
	 * @param cwdb
	 */
	public void setCwDB(InteliCwDB cwdb)
	{
		this.cwdb = cwdb;
	}
	
	/**
	 * 
	 * @param word
	 * @return
	 */
	public boolean contains (String word)
	{
		for(CwEntry e : entries)
		{
			if (e.getWord().equals(word))
				return true;
		}
		return false;
	}
	
	/**
	 * 
	 * @param cwe
	 * @param s
	 */
	public final void addCwEntry(CwEntry cwe, Strategy s)
	{
		entries.add(cwe);
		s.updateBoard(gameBoard, cwe);
	}
	
	/**
	 * 
	 * @param s
	 */
	public final void generate(Strategy s)
	{
		  CwEntry e = null;
		  
		  while((e = s.findEntry(this)) != null)
		  {
			  if (!this.contains(e.getWord()))
				  addCwEntry(e,s);
			  else
				  continue;
		  }
	}
	
	/**
	 * 
	 * @return
	 */
	public long getUniqueID() 
	{
		return new Date().getTime();
	}
	
	/**
	 * 
	 * @return
	 */
	public long getCID() 
	{
		return CID;
	}
}
