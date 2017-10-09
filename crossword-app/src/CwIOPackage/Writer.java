package CwIOPackage;
import java.io.IOException;

import ModelPackage.Crossword;


public interface Writer {
	public void write(Crossword cw) throws IOException;
	long getUniqueID();
}
