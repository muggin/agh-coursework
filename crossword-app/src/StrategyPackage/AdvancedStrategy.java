   package StrategyPackage;

import java.util.BitSet;
import java.util.LinkedList;
import java.util.Random;

import BoardPackage.Board;
import BoardPackage.BoardCell;
import CwDBPackage.InteliCwDB;
import EntryPackage.CwEntry;
import EntryPackage.CwEntry.Direction;
import EntryPackage.Entry;
import ModelPackage.Crossword;

public class AdvancedStrategy extends Strategy {

	/**
	 * 
	 */
	@Override
	public CwEntry findEntry(Crossword cw) {

		Board b = cw.getBoardCopy();
		InteliCwDB cwdb = cw.getCwDB();
		LinkedList<BoardCell> startCells = b.getStartCells();
		Entry e = null;
		
		
		if (startCells.size() == 0 && b.getCell(0, 0).isEmpty())
		{
			int length = b.getWidth() - 1;
			int randomDirection = new Random().nextInt();
			Direction direction;
			
			if (randomDirection % 2 == 0)
				direction = Direction.HORIZ;
			else
				direction = Direction.VERT;
			
			e = cwdb.getRandom(2, length);

			return new CwEntry(e.getWord(), e.getClue(), 0, 0, direction);
		}
		else if (startCells.size() != 0)
		{
			BoardCell bc;
			String pattern;
			Direction direction;
			
			do
			{
				int randomStart = new Random().nextInt(startCells.size());
				bc = startCells.remove(randomStart);
				int endX = bc.getX(), endY = bc.getY();
				
				if (bc.getHorizontal().get(0))
				{
					direction = Direction.HORIZ;
					endY = b.getWidth() - 1;
				}
				else
				{
					direction = Direction.VERT;
					endX = b.getHeight() - 1;
				}
				
				pattern = b.createPattern(bc.getX(), bc.getY(), endX, endY);
				e = cwdb.getRandom(pattern);
				
			} while (e == null && startCells.size() > 0);
			
			if (e == null)
				return null;
			else
				return new CwEntry(e.getWord(), e.getClue(), bc.getX(), bc.getY(), direction);
		}
		else
		{
			return null;
		}
	}
	
	private void updateNext(int posX, int posY, Board b)
	{
	}

	/**
	 * 
	 */
	@Override
	public void updateBoard(Board b, CwEntry e) 
	{
		int horiz = 0, vert = 0;
		for (int i = 0; i < e.getWord().length(); i++)
		{
		BitSet horizontal = new BitSet();
		BitSet vertical = new BitSet();
		horizontal.clear();
		vertical.clear();
		
		if (e.getD() == Direction.HORIZ)
		{
			horiz = 1;
			vertical.set(0,3);
		}
		else
		{
			vert = 1;
			horizontal.set(0,3);
		}
		
		
			int posX = e.getX() + (i * vert);
			int posY = e.getY() + (i * horiz);
			
			b.setCell(posX, posY, new BoardCell(posX, posY, Character.toString(e.getWord().charAt(i)), "", horizontal, vertical));
			
			if (i == 0)
				updateNext(posX, posY, b);
		}
	}
}
