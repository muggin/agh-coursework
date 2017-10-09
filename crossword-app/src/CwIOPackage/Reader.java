package CwIOPackage;
import java.io.IOException;
import java.util.LinkedList;

import ModelPackage.Crossword;


public interface Reader {
	public LinkedList<Crossword> getAllCws() throws IOException, ClassNotFoundException;

}
