package ModelPackage;
import java.awt.Dimension;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.ListIterator;

import StrategyPackage.AdvancedStrategy;
import StrategyPackage.SimpleStrategy;
import StrategyPackage.Strategy;
import EntryPackage.CwEntry;
import CwDBPackage.InteliCwDB;
import CwIOPackage.CwReader;
import CwIOPackage.CwWriter;


public class CwBrowser {
	public static final int MAXDIM = 16;
	public static final int MINDIM = 3;
	private String loadDirectory;
	private String saveDirectory;
	private InteliCwDB cwdb;
	private LinkedList<Crossword> crosswords;
	private ListIterator<Crossword> currentIter;
	private Crossword currentCrossword;
	private Strategy gameStrategy;
	private int heightSet = 10;
	private int widthSet = 10;
	
	
	
	public CwBrowser ()
			throws IOException, FileNotFoundException
	{
		this.cwdb = new InteliCwDB(InteliCwDB.class.getResource("cwdb.txt").getPath());
		this.loadDirectory = System.getProperty("user.dir");
		this.saveDirectory = System.getProperty("user.dir");
		this.crosswords = new LinkedList<Crossword>();
		this.currentIter = null;
		this.currentCrossword = null;
		this.gameStrategy = new SimpleStrategy();
	}
	
	/**
	 * Funkcja sprawdza rozmiar planszy.
	 * @return rozmiar planszy.
	 */
	public Dimension boardDimension()
	{
		if (currentCrossword != null)
			return currentCrossword.cwDimension();
		else
			return null;
	}
	
	/**
	 * Funkcja zmienia baze hasel.
	 * @param cwdbFile - Sciezka do pliku zawierajacego nowa baze hasel.
	 */
	public void changeCwDB (String cwdbFile)
			throws IOException, FileNotFoundException	
	{
		this.cwdb = new InteliCwDB(cwdbFile);
	}
	
	/**
	 * Funkcja sprawdza poprawnosc aktualnego rozwiazania krzyzowki.
	 * @return - informacje na temat poprawnosci rozwiazania.
	 */
	public LinkedList<Boolean> checkBoardSolution()
	{
		if (currentCrossword != null)
			return currentCrossword.checkBoardSolution();
		else
			return null;
	}
	
	/**
	 * Funkcja generuje nowa krzyzowke.
	 */
	public void generateCrossword()
	{
		Crossword cw = new Crossword(this.cwdb, 1, this.heightSet, this.widthSet);
		cw.generate(this.gameStrategy);
		this.crosswords.addLast(cw);
		this.currentIter = crosswords.listIterator(crosswords.size() - 1);
		this.currentCrossword = cw;
	}
	
	/**
	 * Funkcja pobiera prawidlowa zawartosc krzyzowki.
	 * @return - prawidlowe rozwiazanie krzyzowki.
	 */
	public LinkedList<String> getBoardContent()
	{
		if (currentCrossword != null )
		{
			return currentCrossword.getBoardContent();
		}
		return null;
	}
	
	/**
	 * Funkcja pobiera aktualne rozwiazanie krzyzowki.
	 * @return - aktualne rozwiazanie krzyzowki.
	 */
	
	public LinkedList<String> getBoardSolution()
	{
		if (currentCrossword != null )
		{
			return currentCrossword.getBoardSolution();
		}
		return null;
	}
	
	/**
	 * Funkcja sprawdza wykorzystanie pol na planszy.
	 * @return - prawidlowe rozwiazanie krzyzowki.
	 */
	public LinkedList<Boolean> getBoardStatus()
	{
		if (currentCrossword != null)
		{
			return currentCrossword.getBoardStatus();
		}
		return null;
	}
	
	/**
	 * Funkcja pobiera ID aktualnej krzyzowki.
	 * @return - ID aktualnej krzyzowki.
	 */
	public long getCID()
	{
		if (currentCrossword != null)
			return currentCrossword.getCID();
		else
			return -1;
	}
	
	/**
	 * Funkcja pobiera iterator do listy hasel w krzyzowce.
	 * @return - iterator do listy hasel.
	 */
	public Iterator<CwEntry> getEntries()
	{
		if (currentCrossword != null)
			return currentCrossword.getROEntryIter();
		else
			return null;
	}

	/**
	 * Funkcja pobiera ustawiony rozmiar planszy.
	 * @return - aktualna wysokosc planszy.
	 */
	public int getHeightSet() 
	{
		return heightSet;
	}
	
	/**
	 * Funkcja pobiera domyslny folder odczytu pliku.
	 * @return - sciezka do folderu odczytu pliku.
	 */
	public String getLoadDirectory() 
	{
		return loadDirectory;
	}
	
	/**
	 * Funkcja pobiera domyslny folder zapisu pliku.
	 * @return - sciezka do folderu zapisu pliku.
	 */
	public String getSaveDirectory() 
	{
		return saveDirectory;
	}
	
	/**
	 * Funkcja pobiera ustawiony rozmiar planszy.
	 * @return - aktualna szerokosc planszy.
	 */
	public int getWidthSet() 
	{
		return widthSet;
	}
	
	/**
	 * Funkcja przesuwa wskaznik na kolejna krzyzowke na liscie.
	 */
	public void nextCrossword()
	{
		if (currentIter != null && currentIter.hasNext())
			currentCrossword = currentIter.next();
	}
	
	/**
	 * Funkcja otwiera krzyzowke z pliku.
	 * @param openDirectory - Sciezka do pliku z ktorego pobrana ma byc krzyzowka.
	 * @throws IOException
	 * @throws ClassNotFoundException
	 */
	public void openCrossword(String openDirectory)
		throws IOException, ClassNotFoundException
	{
		Crossword cw = new CwReader(openDirectory).getCw(openDirectory);
		this.crosswords.addLast(cw);
		this.currentIter = crosswords.listIterator(crosswords.size() - 1);
		this.currentCrossword = cw;
	}
	
	/**
	 * Funkcja przesuwa wskaznik na poprzednia krzyzowke na liscie.
	 */
	public void prevCrossword()
	{
		if (currentIter != null && currentIter.hasPrevious())
			currentCrossword = currentIter.previous();
	}
	
	/**
	 * Funkcja zapisuje krzyzowke do pliku.
	 * @param saveDirectory - Sciezka do pliku w ktorym ma byc zapisana krzyzowka (.cwf).
	 */
	public void saveCrossword(String saveDirectory) 
			throws IOException
	{
		if (currentCrossword != null)
			new CwWriter(saveDirectory).write(this.currentCrossword);
	}
	
	/**
	 * Funkcja ustawia aktualne rozwiazanie krzyzowki.
	 * @param boardSolution - aktualne rozwiazanie krzyzowki.
	 */
	public void setBoardSolution (LinkedList<String> boardSolution)
	{
		if (currentCrossword != null )
		{
			currentCrossword.setBoardSolution(boardSolution);
		}
	}
	
	/**
	 * Funkcja ustawia rozmiar planszy.
	 * @param setHeight - nowa wysokosc planszy.
	 */
	public void setHeightSet(int setHeight) 
	{
		this.heightSet = setHeight;
	}
	
	/**
	 * Funkcja ustawia rozmiar planszy.
	 * @param setWidth - nowa szerokosc planszy.
	 */
	public void setWidthSet(int setWidth) 
	{
		this.widthSet = setWidth;
	}	
	
	
	public String getGameStrategy() 
	{
		return gameStrategy.getClass().getSimpleName();
	}

	public void setGameStrategy(String gameStrategy) 
	{
		if (gameStrategy.equals("SimpleStrategy"))
			this.gameStrategy = new SimpleStrategy();
		else if (gameStrategy.equals("AdvancedStrategy"))
			this.gameStrategy = new AdvancedStrategy();
	}
	
}
