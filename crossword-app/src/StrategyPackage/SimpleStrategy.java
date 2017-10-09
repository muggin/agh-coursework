package StrategyPackage;

import java.util.BitSet;
import java.util.LinkedList;

import BoardPackage.*;
import CwDBPackage.InteliCwDB;
import EntryPackage.CwEntry;
import EntryPackage.CwEntry.Direction;
import EntryPackage.Entry;
import ModelPackage.Crossword;


public class SimpleStrategy extends Strategy {

	/**
	 * Funkcja znajduje wpis do krzyzowki.
	 * @param cw - generowana krzyzowka.
	 * @return - znaleziony wpis
	 */
	@Override
	public CwEntry findEntry(Crossword cw)
	{
		Board b = cw.getBoardCopy();
		InteliCwDB cwdb = cw.getCwDB();
		LinkedList<BoardCell> startCells = b.getStartCells();
		Entry e = null;
		
		if (startCells.size() == 0 && b.getCell(0, 0).isEmpty())
		{
			int length = b.getHeight();
			
			do
			{
				e = cwdb.getRandom(length);
				length--;
				
			} while (e == null && length > 0);

			return new CwEntry(e.getWord(), e.getClue(), 0, 0, Direction.VERT);
		}
		else if (startCells.size() != 0)
		{
			BoardCell bc = startCells.pop();
			String pattern = b.createPattern(bc.getX(), bc.getY(), bc.getX(), b.getWidth() - 1);
			e = cwdb.getRandom(pattern);
			
			if (e == null)
			{
				return null;
			}
			else
				return new CwEntry(e.getWord(), e.getClue(), bc.getX(), bc.getY(), Direction.HORIZ);
		}
		else
		{
			return null;
		}
	}

	/**
	 * Funkcja uaktualnia tablice stanu gry o nowy wpis.
	 * @param b - tablica stanu gry ktora bedzie uaktualniona.
	 * @param e - nowy wpis do ktore zostanie dodany do tablicy stanu gry.
	 */
	@Override
	public void updateBoard(Board b, CwEntry e) 
	{
		int horiz = 0, vert = 0;
		for (int i = 0; i < e.getWord().length(); i++)
		{
		BitSet horizontal = new BitSet(3);
		BitSet vertical = new BitSet(3);
		horizontal.clear();
		vertical.clear();
		
		if (e.getD() == CwEntry.Direction.HORIZ)
		{
			horiz = 1;
		}
		else
		{
			vert = 1;
			vertical.set(0);
		}
		
		
			int posX = e.getX() + (i * vert);
			int posY = e.getY() + (i * horiz);
			
			b.setCell(posX, posY, new BoardCell(posX, posY, Character.toString(e.getWord().charAt(i)), "", horizontal, vertical));
		}
	}
}
