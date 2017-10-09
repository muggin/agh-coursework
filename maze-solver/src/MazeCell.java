
public class MazeCell {
	
	private final int posX;
	private final int posY;
	private final boolean accesible;
	
	MazeCell (int posX, int posY, boolean accesible)
	{
		this.posX = posX;
		this.posY = posY;
		this.accesible = accesible;
	}
	
	public boolean isAccesible()
	{
		return this.accesible;
	}
	
	public int getPosX()
	{
		return this.posX;
	}
	
	public int getPosY()
	{
		return this.posY;
	}

}
