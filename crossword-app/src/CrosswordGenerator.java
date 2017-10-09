import java.io.FileNotFoundException;
import java.io.IOException;

import GUIPackage.CwWindow;
import ModelPackage.CwBrowser;


public class CrosswordGenerator {
	
	public static void main(String[] args)
	{
		
		CwBrowser crosswordModel = null;
		try {
			crosswordModel = new CwBrowser();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		CwWindow crosswordView = new CwWindow(CwBrowser.MINDIM, CwBrowser.MAXDIM, CwBrowser.MINDIM, CwBrowser.MAXDIM);
		CwController crosswordController = new CwController(crosswordModel, crosswordView);
	}
}
