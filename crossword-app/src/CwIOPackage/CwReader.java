package CwIOPackage;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.LinkedList;

import ModelPackage.Crossword;

public class CwReader implements Reader {
	String cwDirectory;
	LinkedList<Crossword> crosswords;
	
	public CwReader(String cwDirectory)
	{
		this.cwDirectory = cwDirectory;
	}

	@Override
	public LinkedList<Crossword> getAllCws() 
			throws IOException, ClassNotFoundException
	{
		LinkedList<Crossword> crosswords = new LinkedList<Crossword>();
		File directory = new File(cwDirectory);
		
		for(File file : directory.listFiles())
		{
			if (file.isFile() && file.getName().endsWith(".cwf"))
			{
				crosswords.add(getCw(file.toString()));
			}
		}
		
		return crosswords;
	}
	
	public Crossword getCw(String cwFile) 
			throws IOException, ClassNotFoundException
	{
		Crossword newCw;
		ObjectInputStream ois = new ObjectInputStream(new FileInputStream(cwFile));
		newCw = (Crossword) ois.readObject();
		ois.close();
		return newCw;
	}
}
