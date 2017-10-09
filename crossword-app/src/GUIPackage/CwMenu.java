package GUIPackage;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.KeyStroke;

public class CwMenu extends JMenuBar {

	private static final long serialVersionUID = 6990020469389801186L;
	JMenu fileMenu, generatorMenu, helpMenu;
	JMenuItem openItem, saveItem, printItem, importItem, exitItem, generateItem, prevItem, nextItem, checkItem, solveItem, resetItem, optionItem, aboutItem;
	
	public CwMenu()
	{
		fileUI();
		generatorUI();
		helpUI();
	}
	
	/**
	 * Funkcja inicjalizuje i ustawia elementy podmenu FILE.
	 */
	private void fileUI()
	{
		this.fileMenu = new JMenu("File");
		this.fileMenu.setMnemonic(KeyEvent.VK_F);
		this.fileMenu.setToolTipText("File operation menu.");
		
		
		// OPEN option.
		this.openItem = new JMenuItem("Open");
		this.openItem.setToolTipText("Open existing crossword.");
		this.openItem.setActionCommand("openItem");
		fileMenu.add(this.openItem);
				
		// SAVE option.
		this.saveItem = new JMenuItem("Save");
		this.saveItem.setToolTipText("Save current crossword.");
		this.saveItem.setActionCommand("saveItem");
		this.fileMenu.add(this.saveItem);
		
		// PRINT option.
		this.printItem = new JMenuItem("Print");
		this.printItem.setToolTipText("Print current crossword.");
		this.printItem.setActionCommand("printItem");
		this.fileMenu.add(this.printItem);
		
		this.fileMenu.addSeparator();
		
		// IMPORT option.
		this.importItem = new JMenuItem("Import DB");
		this.importItem.setToolTipText("Import crossword database from external file.");
		this.importItem.setActionCommand("importItem");
		this.fileMenu.add(this.importItem);
	
		this.fileMenu.addSeparator();
		
		// EXIT option.
		this.exitItem = new JMenuItem("Exit");
		this.exitItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_W, ActionEvent.CTRL_MASK));
		this.exitItem.setToolTipText("Exit application.");
		this.exitItem.setActionCommand("exitItem");
		this.fileMenu.add(this.exitItem);
		
		add(this.fileMenu);
	}
	
	/**
	 * Funkcja inicjalizuje i ustawia elementy podmenu GENERATOR.
	 */
	private void generatorUI()
	{
		this.generatorMenu = new JMenu("Generator");
		generatorMenu.setMnemonic(KeyEvent.VK_G);
		generatorMenu.setToolTipText("Generator strategy menu.");
		
		// GENERATE option.
		this.generateItem = new JMenuItem("Generate");
		this.generateItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_G, ActionEvent.CTRL_MASK));
		this.generateItem.setToolTipText("Generate new crossword.");
		this.generateItem.setActionCommand("generateItem");
		this.generatorMenu.add(this.generateItem);
		
		// PREV option.
		this.prevItem = new JMenuItem("Previous");
		this.prevItem.setToolTipText("Get previous crossword.");
		this.prevItem.setActionCommand("prevItem");
		this.generatorMenu.add(this.prevItem);
				
		// NEXT option.
		this.nextItem = new JMenuItem("Next");
		this.nextItem.setToolTipText("Get next crossword.");
		this.nextItem.setActionCommand("nextItem");
		this.generatorMenu.add(this.nextItem);
		
		this.generatorMenu.addSeparator();
		
		// CHECK option.
		this.checkItem = new JMenuItem("Check");
		this.checkItem.setToolTipText("Check current crossword.");
		this.checkItem.setActionCommand("checkItem");
		this.generatorMenu.add(this.checkItem);
		
		// SOLVE option.
		this.solveItem = new JMenuItem("Solve");
		this.solveItem.setToolTipText("Solve current crossword.");
		this.solveItem.setActionCommand("solveItem");
		this.generatorMenu.add(this.solveItem);
		
		// RESET option.
		this.resetItem = new JMenuItem("Reset");
		this.resetItem.setToolTipText("Reset current crossword.");
		this.resetItem.setActionCommand("resetItem");
		this.generatorMenu.add(this.resetItem);
		
		this.generatorMenu.addSeparator();
		
		// OPTIONS option.
		this.optionItem = new JMenuItem("Options");
		this.optionItem.setToolTipText("New crossword with default settings.");
		this.optionItem.setActionCommand("optionItem");
		this.generatorMenu.add(this.optionItem);
		
		add(this.generatorMenu);
	}
	
	/**
	 * Funkcja inicjalizuje i ustawia elementy podmenu HELP.
	 */
	private void helpUI()
	{
		this.helpMenu = new JMenu("Help");
		this.helpMenu.setMnemonic(KeyEvent.VK_H);
		this.helpMenu.setToolTipText("Help menu.");
		
		this.aboutItem = new JMenuItem("About");
		this.aboutItem.setToolTipText("Information about this program.");
		this.aboutItem.setActionCommand("aboutItem");
		this.helpMenu.add(this.aboutItem);
		
		add(this.helpMenu);
	}
	
	/**
	 * Funkcja przypisuje kontroler do elementow menu.
	 * @param menuController - kontroler elementow menu.
	 */
	public void setMenuActionController(ActionListener menuController)
	{
		this.openItem.addActionListener(menuController);
		this.saveItem.addActionListener(menuController);
		this.printItem.addActionListener(menuController);
		this.importItem.addActionListener(menuController);
		this.exitItem.addActionListener(menuController);
		this.generateItem.addActionListener(menuController);
		this.prevItem.addActionListener(menuController);
		this.nextItem.addActionListener(menuController);
		this.checkItem.addActionListener(menuController);
		this.solveItem.addActionListener(menuController);
		this.resetItem.addActionListener(menuController);
		this.optionItem.addActionListener(menuController);
		this.aboutItem.addActionListener(menuController);
	}
}
