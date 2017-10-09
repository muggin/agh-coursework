import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.LinkedList;


public class Maze {
	
	private MazeCell [][] maze;
	private int sizeX;
	private int sizeY;
	private MazeCell mazeStart;
	private MazeCell mazeEnd;
	
	Maze (InputStream fileStream)
	{
		this.mazeStart = null;
		this.mazeEnd = null;
		this.maze = null;
		loadMaze(fileStream);
	}
	
	private void loadMaze (InputStream fileStream)
	{
		try 
		{
			BufferedReader input = new BufferedReader(new InputStreamReader(fileStream));
			String[] currentLine;
			
			currentLine = input.readLine().split(" ");
			sizeX = Integer.parseInt(currentLine[0]);
			sizeY = Integer.parseInt(currentLine[1]);
			
			this.maze = new MazeCell[sizeX][];
			
			for (int x = 0; x < sizeX; x++)
			{
				maze[x] = new MazeCell[sizeY];
				currentLine = input.readLine().split("(?!^)");
				
				for (int y = 0; y < sizeY; y++)
				{
					if (currentLine[y].equals("#"))
						this.maze[x][y] = new MazeCell(x, y, false);
					else if (currentLine[y].equals("0"))
						this.maze[x][y] = new MazeCell(x, y, true);
					else if (currentLine[y].equals("E"))
						this.maze[x][y] = this.mazeStart = new MazeCell(x, y, true);
					else if (currentLine[y].equals("X"))
						this.maze[x][y] = this.mazeEnd = new MazeCell(x, y, true);
				}
			}
			
			input.close();
			
			System.out.println("Maze loaded. Size: " + sizeX + " x " + sizeY);
		} 
		catch (IOException e) 
		{
			System.out.println("Error while loading maze.");
			e.printStackTrace();
		} 
	}
	
	public LinkedList<MazeCell> getNeighbours(MazeCell currentLocation)
	{
		LinkedList<MazeCell> neighbourList = new LinkedList<MazeCell>();
		int posX = currentLocation.getPosX();
		int posY = currentLocation.getPosY();
		
		if (posX > 0)
			if (this.maze[posX - 1][posY].isAccesible()) neighbourList.add(this.maze[posX - 1][posY]);
		
		if (posY > 0)
			if (this.maze[posX][posY - 1].isAccesible()) neighbourList.add(this.maze[posX][posY - 1]);
		
		if (posX < sizeX - 1)
			if (this.maze[posX + 1][posY].isAccesible()) neighbourList.add(this.maze[posX + 1][posY]);
		
		if (posY < sizeY - 1)
			if (this.maze[posX][posY + 1].isAccesible()) neighbourList.add(this.maze[posX][posY + 1]);
		
		return neighbourList;
	}
	
	public MazeCell getStartCell()
	{
		return this.mazeStart;
	}
	
	public MazeCell getEndCell()
	{
		return this.mazeEnd;
	}
	
	public MazeCell getCell(int x, int y)
	{
		return this.maze[x][y];
	}
	
	public int getSizeX()
	{
		return this.sizeX;
	}
	
	public int getSizeY()
	{
		return this.sizeY;
	}
	
	public void printMaze()
	{
		int block;
		for (int x = 0; x < this.sizeX; x++)
		{
			for (int y = 0; y < this.sizeY; y++)
			{
				block = (this.maze[x][y].isAccesible()) ? 0: 1;
				System.out.print(block);
			}
			System.out.println();
		}
		
		System.out.print("0, 0: " + this.maze[0][0]);
	}
	
}
