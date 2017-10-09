import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.print.PrinterException;
import java.io.FileNotFoundException;
import java.io.IOException;

import GUIPackage.CwWindow;
import ModelPackage.CwBrowser;


public class CwController implements ActionListener {
	CwBrowser cwModel;
	CwWindow cwView;
	
	public CwController (CwBrowser cwModel, CwWindow cwView)
	{
		this.cwModel = cwModel;
		this.cwView = cwView;
		this.cwView.setActionController(this);
	}

	/**
	 * 
	 * @param e
	 */
	@Override
	public void actionPerformed(ActionEvent e) {
		
		if (e.getActionCommand() == "openItem")
		{
			String filePath = cwView.openFile(this.cwModel.getLoadDirectory(), "cwf");
			if (filePath != null)
			{
				try 
				{
					cwModel.openCrossword(filePath);
					cwView.draw(cwModel.boardDimension(), cwModel.getBoardStatus(), cwModel.getCID(), cwModel.getEntries());
					cwView.setContent(cwModel.getBoardSolution());
				} 
				catch (IOException e1) 
				{
					cwView.errorMessage("Error occured while loading file.");
				} 
				catch (ClassNotFoundException e1) 
				{
					cwView.errorMessage("Error occured while loading file.");
				}
			}
			System.out.println(filePath);
		}
		else if (e.getActionCommand() == "saveItem")
		{
			String filePath = cwView.saveFile(this.cwModel.getSaveDirectory());
			if (filePath != null)
			{
				try 
				{
					cwModel.setBoardSolution(cwView.getContent());
					cwModel.saveCrossword(filePath);
				} 
				catch (IOException e1) 
				{
					cwView.errorMessage("Error occured while saving crossword.");
				}
				System.out.println(filePath);
			}	
		}
		else if (e.getActionCommand() == "printItem")
		{
			try 
			{
				cwView.printContents();
			} 
			catch (PrinterException e1) 
			{
				cwView.errorMessage("Error occured while printing crossword.");
				e1.printStackTrace();
			}
		}
		else if (e.getActionCommand() == "importItem")
		{
			String filePath = cwView.openFile(this.cwModel.getLoadDirectory(), "txt");
			if (filePath != null)
			{
				try 
				{
					cwModel.changeCwDB(filePath);
				} 
				catch (FileNotFoundException e1) 
				{
					cwView.errorMessage("Selected file was not found.");
					e1.printStackTrace();
				} 
				catch (IOException e1) 
				{
					cwView.errorMessage("Error while loading database file.");
					e1.printStackTrace();
				}
			}
			System.out.println(filePath);
		}
		else if (e.getActionCommand() == "exitItem")
		{
			System.exit(0);
		}
		else if (e.getActionCommand() == "generateItem")
		{
			cwModel.setBoardSolution(cwView.getContent());
			cwModel.generateCrossword();
			cwView.draw(cwModel.boardDimension(), cwModel.getBoardStatus(), cwModel.getCID(), cwModel.getEntries());
			System.out.println("GENERATE!");
		}
		else if (e.getActionCommand() == "prevItem")
		{
			cwModel.setBoardSolution(cwView.getContent());
			cwModel.prevCrossword();			
			cwView.draw(cwModel.boardDimension(), cwModel.getBoardStatus(), cwModel.getCID(), cwModel.getEntries());
			cwView.setContent(cwModel.getBoardSolution());
			System.out.println("PREVIOUS!");
		}
		else if (e.getActionCommand() == "nextItem")
		{
			cwModel.setBoardSolution(cwView.getContent());
			cwModel.nextCrossword();
			cwView.draw(cwModel.boardDimension(), cwModel.getBoardStatus(), cwModel.getCID(), cwModel.getEntries());
			cwView.setContent(cwModel.getBoardSolution());
			System.out.println("NEXT!");
		}
		else if (e.getActionCommand() == "checkItem")
		{
			cwModel.setBoardSolution(cwView.getContent());
			cwView.checkContent(cwModel.checkBoardSolution());
		}
		else if (e.getActionCommand() == "solveItem")
		{
			cwView.setContent(cwModel.getBoardContent());
			System.out.println("SOLVE!");
		}
		else if (e.getActionCommand() == "resetItem")
		{
			System.out.println("RESET Option clicked!");
			cwView.cleanContent();
		}
		else if (e.getActionCommand() == "optionItem")
		{
			cwView.showOptions(cwModel.getHeightSet(), cwModel.getWidthSet(), cwModel.getGameStrategy());
			cwModel.setHeightSet(cwView.getHeightSet());
			cwModel.setWidthSet(cwView.getWidthSet());
			cwModel.setGameStrategy(cwView.getGameStrategy());
			
			System.out.println("OPTIONS Option clicked!");
		}
		else if (e.getActionCommand() == "aboutItem")
		{
			String message = "PROJEKT - KOLOKWIUM.\nPrzedmiot: Programowanie Obiektowe.\nAutor: Wojciech Kryscinski\nData: 10.12.2013";
			cwView.helpMessage(message);
		}
	}
}
