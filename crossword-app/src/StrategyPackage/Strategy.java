package StrategyPackage;

import BoardPackage.Board;
import EntryPackage.CwEntry;
import ModelPackage.Crossword;


public abstract class Strategy {

	/**
	 * Funkcja zwraca kolejny wpis do krzyzowki.
	 * @param cw
	 * @return
	 */
	public abstract CwEntry findEntry(Crossword cw);
	
	/**
	 * Funkcja uaktualnia tablice stanu gry o nowy wpis.
	 * @param b - tablica stanu gry ktora bedzie uaktualniona.
	 * @param e - nowy wpis do ktore zostanie dodany do tablicy stanu gry.
	 */
	public abstract void updateBoard(Board b, CwEntry e);
}
