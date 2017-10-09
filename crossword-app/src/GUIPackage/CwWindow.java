package GUIPackage;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.ActionListener;
import java.awt.print.PrinterException;
import java.awt.print.PrinterJob;
import java.text.SimpleDateFormat;
import java.util.Iterator;
import java.util.LinkedList;

import javax.swing.BorderFactory;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.swing.text.AttributeSet;
import javax.swing.text.BadLocationException;
import javax.swing.text.PlainDocument;

import EntryPackage.CwEntry;
import EntryPackage.CwEntry.Direction;

public class CwWindow extends JFrame {

	private static final long serialVersionUID = 8370449744300782063L;
	private static final int MAXDIM = 16;
	private CwContent contentPanel =  null;
	private JLabel headerPanel = null;
	private CwOptions optionWindow = null;
	private CwMenu menu = null;
	static final int cellSize = 36;
	static final int borderSize = 10;
	static final int headerHeight = 40;
	final Color boxBorder = Color.black;
	final Color boxFill = new Color(240, 240, 240);
	final Color normalFont = Color.black;
	final Color validFont = Color.green.darker();
	final Color errorFont = Color.red;
	private int startPosX = 0;
	private int startPosY = 0;
	
	public CwWindow(int heightMin, int heightMax, int widthMin, int widthMax)
	{
		initUI(heightMin, heightMax, widthMin, widthMax);
		setVisible(true);
	}
	
	/**
	 * Funkcja inicjalizuje i ustawia glowne okno GUI.
	 */
	private void initUI(int heightMin, int heightMax, int widthMin, int widthMax)
	{
		setTitle("WK Crosswords");
		setResizable(false);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		
		BorderLayout windowLayout = new BorderLayout();
		windowLayout.preferredLayoutSize(this);
		
		menu = new CwMenu();
		optionWindow = new CwOptions(heightMin, heightMax, widthMin, widthMax);
		contentPanel = new CwContent();
		
		headerPanel = new JLabel("Crossword");
		headerPanel.setHorizontalAlignment(SwingConstants.CENTER);
		headerPanel.setBorder(new EmptyBorder(borderSize, borderSize, borderSize,borderSize));
		
		
		setJMenuBar(menu);
		add(contentPanel, BorderLayout.CENTER);
		add(headerPanel, BorderLayout.NORTH);
		pack();
		setLocationRelativeTo(null);
	}
	
	/**
	 * Funkcja przypisuje ustawia kontroler obiektow graficznych.
	 * @param crosswordController - kontroler obiektow graficznych.
	 */
	public void setActionController(ActionListener crosswordController)
	{
		menu.setMenuActionController(crosswordController);
	}
	
	/**
	 * \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	 * ========= WYSWIETLANIE KRZYZOWKI =========
	 * \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	 */
	
	/**
	 * Funkcja wyswietla wypelniona krzyzowke wraz z podpowiedziami.
	 * @param boardDimension - Rozmiary krzyzowki.
	 * @param boardStatus - Informacja o wykorzystaniu pol krzyzowki.
	 * @param CID - Identyfikator krzyzowki.
	 * @param entries - Lisa hasel znajdujacych sie w krzyzowce.
	 */
	public void draw(Dimension boardDimension, LinkedList<Boolean> boardStatus, long CID, Iterator<CwEntry> entries)
	{
		if (boardDimension != null)
		{
			drawCrossword(boardDimension, boardStatus, CID);
			printClues(entries);
		}
		else
		{
			cleanCwPanel();
			cleanCluePanel();
		}
	}
	
	/**
	 * Funkcja wyswietla pusta strukture krzyzowki.
	 * @param boardDimension - Rozmiary krzyzowki.
	 * @param boardStatus - Informacja o wykorzystaniu pol krzyzowki.
	 * @param CID - Identyfikator krzyzowki.
	 */
	public void drawCrossword(Dimension boardDimension, LinkedList<Boolean> boardStatus, long CID)
	{
		cleanCwPanel();
		headerPanel.setText("Crossword generation date: " + new SimpleDateFormat("dd-MM-yyyy HH:mm").format(CID));
		setStartPos(findRealDim(boardDimension, boardStatus), boardDimension);
		int currentX = startPosX;
		int currentY = startPosY;
		int topBorder = 1;
		int leftBorder = 1;
		
		for (int h = 0; h < boardDimension.height; h++)
		{
			for (int w = 0; w < boardDimension.width; w++)
			{
				if (boardStatus.pop())
				{
					JTextField textField = new JTextField(1);
					textField.setHorizontalAlignment(SwingConstants.CENTER);
					textField.setSize(cellSize, cellSize);
					textField.setBackground(boxFill);
					textField.setBorder(BorderFactory.createMatteBorder(topBorder, leftBorder, 1, 1, boxBorder));
					textField.setLocation(currentX, currentY);
					textField.setVisible(true);
					textField.setDocument(new JTextFieldLimit(1));
					contentPanel.fieldList.add(textField);
				
					contentPanel.cwPanel.add(textField);
				}
				
				leftBorder = 0;
				currentX += cellSize;
			}
			currentX = this.startPosX;
			currentY += cellSize;
			topBorder = 0;
			leftBorder = 1;
		}
		contentPanel.cwPanel.repaint();
	}
	
	/**
	 * Funkcja wstawia do pol krzyzowki przekazane wartosci.
	 * @param content - Lista zawartosci pol krzyzowki.
	 */
	public void setContent (LinkedList<String> content)
	{
		if (contentPanel.fieldList != null && content != null)
		{
			for (int i = 0; i < contentPanel.fieldList.size(); i++)
			{
				contentPanel.fieldList.get(i).setText(content.get(i).toUpperCase());
				//contentPanel.fieldList.get(i).setEditable(false);
			}
		}
	}
	
	/**
	 * Funkcja pobiera z krzyzowki zawartosci pol.
	 * @return - Lista zawartosci pol krzyzowki.
	 */
	public LinkedList<String> getContent()
	{
		LinkedList<String> result = null;
		if (contentPanel.fieldList != null)
		{
			result = new LinkedList<String>();
			
			for(JTextField field : contentPanel.fieldList)
				result.add(field.getText());
		}
		return result;
	}
	
	/**
	 * Funkcja wyswietla poprawnosc zawartosci krzyzowki.
	 * @param solutionStatus - Lista poprawnosci zawartosci pol.
	 */
	public void checkContent(LinkedList<Boolean> solutionStatus)
	{
		if (contentPanel.fieldList != null && solutionStatus != null)
		{
			for (int i = 0; i < contentPanel.fieldList.size(); i++)
			{
				if (solutionStatus.get(i))
				{
					contentPanel.fieldList.get(i).setForeground(validFont);
					contentPanel.fieldList.get(i).setEditable(false);
				}
				else
				{
					contentPanel.fieldList.get(i).setForeground(errorFont);
					contentPanel.fieldList.get(i).setEditable(false);
				}
			}
		}
	}
	
	/**
	 * Funkcja czysci pola krzyzowki.
	 */
	public void cleanContent()
	{
		if (contentPanel.fieldList != null)
		{
			for (JTextField field : contentPanel.fieldList)
			{
				field.setText(null);
				field.setForeground(normalFont);
				field.setEditable(true);
			}
		}
	}
	
	/**
	 * Funkcja czysci panel glowny krzyzowki.
	 */
	public void cleanCwPanel()
	{
		contentPanel.fieldList.clear();
		contentPanel.cwPanel.removeAll();
		headerPanel.setText("");
	}
	
	/**
	 * Funkcja wypisuje hasla oraz etykiety na krzyzowce.
	 * @param entries - Lista hasel w krzyzowce.
	 */
	public void printClues(Iterator<CwEntry> entries)
	{
		if (entries != null)
		{
			int horizontalCount = 0, verticalCount = 0;
			StringBuilder horizontalSb = new StringBuilder("POZIOMO:\n\n");
			StringBuilder verticalSb = new StringBuilder("PIONOWO:\n\n");
			CwEntry currentWord = null;
			
			while (entries.hasNext())
			{
				currentWord = entries.next();
				JLabel cwLabel = new JLabel();
				cwLabel.setSize(cellSize, cellSize);
				cwLabel.setHorizontalAlignment(SwingConstants.RIGHT);
				
				if(currentWord.getD() == Direction.HORIZ)
				{
					horizontalCount++;
					cwLabel.setText(Integer.toString(horizontalCount) + " ");
					cwLabel.setVerticalAlignment(SwingConstants.TOP);
					cwLabel.setLocation(startPosX + (currentWord.getY() - 1) * cellSize, startPosY + currentWord.getX() * cellSize);
					
					horizontalSb.append(horizontalCount);
					horizontalSb.append(". ");
					horizontalSb.append(currentWord.getClue());
					horizontalSb.append(" \n");
				}
				else
				{
					verticalCount++;
					
					cwLabel.setText(Integer.toString(verticalCount) + " ");
					cwLabel.setVerticalAlignment(SwingConstants.BOTTOM);
					cwLabel.setLocation(startPosX + currentWord.getY() * cellSize, startPosY + (currentWord.getX() - 1) * cellSize);
					
					verticalSb.append(verticalCount);
					verticalSb.append(". ");
					verticalSb.append(currentWord.getClue());
					verticalSb.append(" \n");
					
				}
				contentPanel.cwPanel.add(cwLabel);
			}
			contentPanel.horizontalClues.setText(horizontalSb.toString());
			contentPanel.verticalClues.setText(verticalSb.toString());
		}
		else
			cleanCluePanel();
	}
	
	/**
	 * Funkcja czysci panel zawierajacy podpowiedzi.
	 */
	public void cleanCluePanel()
	{
		contentPanel.horizontalClues.setText("");
		contentPanel.verticalClues.setText("");
	}
	
	/**
	 * Funkcja wylicza rzeczywisty rozmiar krzyzowki (na podstawie dlugosci zawartych hasel).
	 * @param boardDimension - rozmiary planszy.
	 * @param boardStatus - Lista zajetosci pol krzyzowki.
	 * @return 
	 */
	public Dimension findRealDim (Dimension boardDimension, LinkedList<Boolean> boardStatus)
	{
		int realX = 0, realY = 0;
		for (int i = 0; i < boardDimension.height; i++)
		{
			for (int j = 0; j < boardDimension.width; j++)
			{
				if (boardStatus.get(i * boardDimension.width + j))
				{
					//System.out.println(i + " " + j);
					if (i > realY)
						realY = i;
					if (j > realX)
						realX = j;
				}
				
			}
		}
		return new Dimension(realX + 1, realY + 1);
	}
	
	/**
	 * Funkcja ustawia pozycje startowa do rysowania krzyzowki.
	 * @param realDimension - rzeczywiste rozmiary krzyzowki.
	 * @param boardDimension - rozmiary planszy.
	 */
	private void setStartPos(Dimension realDimension, Dimension boardDimension)
	{
		this.startPosX = (1 + (MAXDIM - realDimension.width) / 2) * cellSize;
		this.startPosY = (1 + (MAXDIM - realDimension.height) / 2) * cellSize;
	}
	
	/**
	 * \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	 * =========== WYSWIETLANIE BLEDOW ==========
	 * \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	 */
	
	/**
	 * Funkcja wyswietla komunikat o zaistnialym bledzie.
	 * @param message - Komunikat zwiazany z bledem.
	 */
	public void errorMessage(String message)
	{
		JOptionPane.showMessageDialog(null, message, "Error!", JOptionPane.ERROR_MESSAGE);
	}
	
	/**
	 * \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	 * =========== WYSWIETLANIE HELPU ===========
	 * \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	 */
	/**
	 * Funkcja wyswietla komunikat o zaistnialym bledzie.
	 * @param message - Komunikat zwiazany z bledem.
	 */
	public void helpMessage(String message)
	{

		JOptionPane.showMessageDialog(null, message, "Crossword Generator", JOptionPane.INFORMATION_MESSAGE);
	}
	
	/**
	 * \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	 * ========== ZAPIS/ODCZYT PLIKOW ===========
	 * \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	 */
	
	/**
	 * Funkcja wyswietlajaca panel ladowania pliku.
	 * @param loadDirectory - Sciezka do folderu ladowania.
	 * @param fileExtension - Poszukiwane rozszerzenie pliku.
	 * @return - Sciezka do pliku.
	 */
	public String openFile (String loadDirectory, String fileExtension)
	{
		String result = null;
		JFileChooser fileDialog = new JFileChooser(loadDirectory);
		fileDialog.setAcceptAllFileFilterUsed(false);
		fileDialog.setFileFilter(new FileNameExtensionFilter(fileExtension, fileExtension));
		int returnValue = fileDialog.showOpenDialog(null);
		if (returnValue == JFileChooser.APPROVE_OPTION)
		{
			System.out.println(fileDialog.getSelectedFile());
			result = fileDialog.getSelectedFile().toString().trim();
		
		}
		return result;
	}
	
	/**
	 * Funkcja wyswietla panel zapisywania pliku.
	 * @param saveDirectory - Sciezka do folderu zapisywania.
	 * @return - Sciezka do pliku.
	 */
	public String saveFile(String saveDirectory)
	{
		String result = null;
		JFileChooser fileDialog = new JFileChooser(saveDirectory);
		fileDialog.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
		int returnValue = fileDialog.showSaveDialog(null);
		if (returnValue == JFileChooser.APPROVE_OPTION)
		{
			System.out.println(fileDialog.getSelectedFile());
			result = fileDialog.getSelectedFile().toString().trim();
		
		}
		return result;
	}
	
	
	
	/**
	 * \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	 * =========== WYSWIETLANIE OPCJI ===========
	 * \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	 */
	
	/**
	 * Funkcja wyswietla panel opcji programu.
	 * @param currentHeight - aktualna wysokosc planszy.
	 * @param currentWidth - aktualna szerokosc planszy.
	 */
	public void showOptions(int currentHeight, int currentWidth, String gameStrategy)
	{
		optionWindow.openOptions(currentHeight, currentWidth, gameStrategy);
	}
	
	/**
	 * Funkcja pobiera wprowadzony rozmiar planszy.
	 * @return - wysokosc planszy.
	 */
	public int getHeightSet()
	{
		return optionWindow.getHeightSet();
	}
	
	/**
	 * Funkcja pobiera wprowadzony rozmiar planszy.
	 * @return - szerokosc planszy.
	 */
	public int getWidthSet()
	{
		return optionWindow.getWidthSet();
	}
	
	public String getGameStrategy()
	{
		return optionWindow.getGameStrategy();
	}
	
	
	/**
	 * \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	 * ========== DRUKOWANIE KRZYZOWKI ==========
	 * \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	 */
	
	/**
	 * Funkcja pokazuje panel drukowania krzyzowki.
	 */
	public void printContents () throws PrinterException
	{
		PrinterJob printJob = PrinterJob.getPrinterJob();
		printJob.setPrintable(contentPanel);
		if (printJob.printDialog())
		{
			printJob.print();
		}
	}
	
	
	/**
	 * Klasa pomocnicza. Ustawia limit wprowadzonych znakow w pojedynczym polu krzyzowki.
	 */
	class JTextFieldLimit extends PlainDocument {
		private static final long serialVersionUID = 6791775599547333536L;
		private int limit;
		
		JTextFieldLimit(int limit) 
		{
			super();
		    this.limit = limit;
		}

		JTextFieldLimit(int limit, boolean upper) 
		{
			super();
		    this.limit = limit;
		}

		@Override
		public void insertString(int offset, String str, AttributeSet attr) throws BadLocationException 
		{
			if (str == null)
				return;

		    if ((getLength() + str.length()) <= limit) 
		    {
		    	super.insertString(offset, str, attr);
		    }
		}
	}
}
