package CwIOPackage;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.util.Date;

import ModelPackage.Crossword;

public class CwWriter implements Writer {
	String cwDirectory;
	
	public CwWriter(String cwDirectory)
	{
		this.cwDirectory = cwDirectory;
	}
	

	@Override
	public void write(Crossword cw) 
			throws IOException
	{
		StringBuilder cwFile = new StringBuilder(this.cwDirectory);
		cwFile.append(cw.getCID());
		cwFile.append(".cwf");
		
		ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(cwFile.toString()));
		oos.writeObject(cw);
		oos.close();
	}

	@Override
	public long getUniqueID() 
	{
		return new Date().getTime();
	}

}
