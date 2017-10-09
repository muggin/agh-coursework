import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;

public class Robot {
	
	private final Maze maze;
	private MazeCell currentLocation;
	private LinkedList<MazeCell> cellStack;
	private LinkedList<MazeCell> mazeSolution;
	private LinkedList<MazeCell> fullPath;
	private HashMap<MazeCell, Integer> visitedCells;
	
	Robot (Maze maze)
	{
		this.maze = maze;
		this.visitedCells = new HashMap<MazeCell, Integer>();
		this.cellStack = new LinkedList<MazeCell>();
		this.mazeSolution = new LinkedList<MazeCell>();
		this.fullPath = new LinkedList<MazeCell>();
		this.currentLocation = maze.getStartCell();
		this.visitedCells.put(maze.getStartCell(), 0);
	}
	
	private void stepForward(MazeCell nextLocation)
	{
		this.currentLocation = nextLocation;
		this.visitedCells.put(nextLocation, this.visitedCells.get(nextLocation) + 1);	
		this.fullPath.addLast(currentLocation);
		this.mazeSolution.push(this.currentLocation);
	}
	
	private void stepBackward(MazeCell nextLocation)
	{
		this.visitedCells.put(this.currentLocation, this.visitedCells.get(this.currentLocation) + 1);
		this.fullPath.addLast(currentLocation);
		this.currentLocation = nextLocation;
		this.mazeSolution.pop();
	}
	
	private void analyzeNeighbours()
	{
		LinkedList<MazeCell> neighbourList = filterNeighbours(this.maze.getNeighbours(this.currentLocation));
		
		for (MazeCell cell : neighbourList)
			this.cellStack.push(cell);
		
	}
	
	private MazeCell nextStep()
	{
		MazeCell nextCell = cellStack.pop();
		
		if (!this.visitedCells.containsKey(nextCell))
			this.visitedCells.put(nextCell, 0);
		
		return nextCell;
	}
	
	private LinkedList<MazeCell> filterNeighbours(LinkedList<MazeCell> neighbourList)
	{
		LinkedList<MazeCell> newNeighbourList = new LinkedList<MazeCell>();
		for (MazeCell cell : neighbourList)
		{
			if (!this.visitedCells.containsKey(cell))
				newNeighbourList.addLast(cell);
			else if (this.visitedCells.get(cell) == 1)
				newNeighbourList.addFirst(cell);
		}
		return newNeighbourList;
	}
	
	public LinkedList<MazeCell> getFullPath()
	{
		return this.fullPath;
	}
	
	public LinkedList<MazeCell> getMazeSolution()
	{
		return this.mazeSolution;
	}
	
	public void solveMaze()
	{
		int i = 1;
		MazeCell nextLocation;
		this.cellStack.add(this.maze.getStartCell());
		
		do
		{
			nextLocation = nextStep();
			if (this.visitedCells.get(nextLocation) == 0)
				stepForward(nextLocation);
			else if (this.visitedCells.get(nextLocation) == 1)
				stepBackward(nextLocation);
			analyzeNeighbours();
			i++;
			
			System.out.println("Iteration " + i);
			//System.out.println("nextLocation: " + nextLocation);
			//System.out.println("currentLocation - X: " + this.currentLocation.getPosX() + " Y: " + this.currentLocation.getPosY());
		}
		while (this.currentLocation != this.maze.getEndCell() && !this.cellStack.isEmpty());
		
		Collections.reverse((LinkedList<MazeCell>) this.mazeSolution);
		
		for (MazeCell cell : this.mazeSolution)
			System.out.println("X: " + cell.getPosX() + " Y: " + cell.getPosY());
		System.out.println("Solution length: " + this.mazeSolution.size());
		System.out.println("Path length: " + this.fullPath.size());
		System.out.println("Finished.");
	}
	
	/*
	public static void main (String [] args)
	{
		Maze maze = new Maze("/Users/Wojtek/Dropbox/Studia/Java/Projekty/Labirynt/src/labirynt.txt");
		Robot robot = new Robot (maze);
		robot.solveMaze();
	}
	*/

}
