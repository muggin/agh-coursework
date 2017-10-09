package GUIPackage;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GridLayout;
import java.awt.geom.AffineTransform;
import java.awt.print.PageFormat;
import java.awt.print.Printable;
import java.awt.print.PrinterException;
import java.util.LinkedList;

import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.ScrollPaneConstants;
import javax.swing.border.LineBorder;

public class CwContent extends JPanel implements Printable {
	
	private static final long serialVersionUID = -4448322469764255220L;
	static final int borderSize = 10;
	static final int panelHight = 648;
	static final int cwWidth = 648;
	static final int clueWidth = 350;
	final Color bgColor = Color.white;
	final Color boxBorder = Color.black;
	final Color normalFont = Color.black;
	final Color validFont = Color.green.darker();
	final Color errorFont = Color.red;
	LinkedList<JTextField> fieldList;
	
	JScrollPane horizontalScrollPane, verticalScrollPane, cwScrollPane;
	JPanel headerPanel, gamePanel, cluePanel, cwPanel;
	JTextArea horizontalClues, verticalClues;
	JTextField cwName;
	JLabel cwLabel;
	
	
	CwContent()
	{
		fieldList = new LinkedList<JTextField>();
		initUI();
		gameUI();
	}
	

	/**
	 * Funkcja inicjalizuje i ustawia glowne okno GUI.
	 */
	private void initUI()
	{
		setLayout(new GridLayout(1,2));
		setBorder(new LineBorder(Color.white, 5, true));
		//setBorder(new EmptyBorder(0, borderSize, borderSize, borderSize));
		setVisible(true);
	}
	
	/**
	 * Funkcja inicjalizuje i ustawia panel gry GUI.
	 */
	private void gameUI()
	{
		gamePanel = new JPanel();
		gamePanel.setLayout(new FlowLayout(FlowLayout.LEADING, 0, 0));
		gamePanel.setVisible(true);
		innerGameUI();
		
		add(gamePanel, BorderLayout.CENTER);
	}
	
	/**
	 * Funkcja inicjalizuje i ustawia panele wewnatrz panely gry.
	 */
	private void innerGameUI()
	{
		cwPanel = new JPanel();
		cwPanel.setLayout(null);
		cwPanel.setBackground(this.bgColor);
		cwScrollPane = new JScrollPane(cwPanel);
		cwScrollPane.setPreferredSize(new Dimension(cwWidth, panelHight));
		cwScrollPane.setBorder(BorderFactory.createTitledBorder("Crossword"));
		cwScrollPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
		cwScrollPane.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		
		gamePanel.add(cwScrollPane);
		
		cluePanel = new JPanel();
		cluePanel.setLayout(new GridLayout(2, 1));
		cluePanel.setPreferredSize(new Dimension(clueWidth, panelHight));
		cluePanel.setBackground(Color.white);
		cluePanel.setBorder(BorderFactory.createTitledBorder("Clues"));
		cluePanel.setVisible(true);
		
		horizontalClues = new JTextArea();
		horizontalClues.setLineWrap(true);
		horizontalClues.setWrapStyleWord(true);
		horizontalClues.setEditable(false);

		horizontalScrollPane = new JScrollPane(horizontalClues);
		horizontalScrollPane.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));
		horizontalScrollPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
		horizontalScrollPane.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
		cluePanel.add(horizontalScrollPane);
		
		verticalClues = new JTextArea();
		verticalClues.setLineWrap(true);
		verticalClues.setWrapStyleWord(true);
		verticalClues.setEditable(false);
		
		verticalScrollPane = new JScrollPane(verticalClues);
		verticalScrollPane.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));
		verticalScrollPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
		verticalScrollPane.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
		cluePanel.add(verticalScrollPane);
		
		gamePanel.add(cluePanel);
	}
		
	/**
	 * Funkcja przeksztalca panel na potrzeby drukowania.
	 * @param g
	 * @param pf
	 * @param index
	 * @return
	 */
	public int print(Graphics g, PageFormat pf, int index) throws PrinterException 
	{
		Graphics2D g2 = (Graphics2D)g;
		if (index >= 1)
		{
			return Printable.NO_SUCH_PAGE;
		}
		else 
		{
			AffineTransform originalTransform = g2.getTransform();
			double scaleX = pf.getImageableWidth() / this.getWidth();
			double scaleY = pf.getImageableHeight() / this.getHeight();
			double scale = Math.min(scaleX, scaleY);
			g2.translate(pf.getImageableX(), pf.getImageableY());
			g2.scale(scale, scale);
			this.printAll(g2);

			g2.setTransform(originalTransform);
		}
		return Printable.PAGE_EXISTS;
	}

}
