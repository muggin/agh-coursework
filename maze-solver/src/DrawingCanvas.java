import java.awt.AlphaComposite;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.util.Iterator;
import java.util.LinkedList;

import javax.swing.JPanel;
import javax.swing.Timer;


public class DrawingCanvas extends JPanel {
	private static final long serialVersionUID = 1L;
	private int cellSize;
	private int heightOffset;
	private int widthOffset;
	private int imageHeight;
	private int imageWidth;
	private int cellsHeight;
	private int cellsWidth;
	Maze maze;
	
	BufferedImage image;
	Graphics2D g2d;
		
	public DrawingCanvas (int cellsHeight, int cellsWidth)
	{
		setBackground(Color.black);
		this.cellsHeight = cellsHeight;
		this.cellsWidth = cellsWidth;
	}
	
	@Override
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);

		if (image == null)
		{
			calculateDimensions();
			createEmptyImage();
		}

		g.drawImage(image, this.widthOffset, this.heightOffset, null);
		
	}
	
	private void createEmptyImage()
	{
		image = new BufferedImage(this.imageWidth, this.imageHeight, BufferedImage.TYPE_INT_ARGB);
		g2d = (Graphics2D)image.getGraphics();
	}
	
	private void calculateDimensions()
	{
		this.cellSize = (2 * cellsHeight > cellsWidth) ? getHeight() / cellsHeight : getWidth() / cellsWidth;
		this.imageHeight = cellsHeight * cellSize;
		this.imageWidth = cellsWidth * cellSize;
		this.heightOffset = (getHeight() - imageHeight) / 2;
		this.widthOffset = (getWidth() - imageWidth) / 2;
		
	}

	public void addMaze(Maze maze)
	{
		// Draw entire maze.
		for (int x = 0; x < maze.getSizeX(); x++)
		{
			for (int y = 0; y < maze.getSizeY(); y++)
			{
				if (maze.getCell(x, y).isAccesible())
					g2d.setColor(Color.white);
				else
					g2d.setColor(Color.black);
					
					g2d.fillRect(y * cellSize, x * cellSize, cellSize, cellSize);
			}
		}
		
		// Set maze start to green.
		g2d.setColor(Color.green);
		g2d.fillRect(maze.getStartCell().getPosY() * cellSize, maze.getStartCell().getPosX() * cellSize, cellSize, cellSize);
		
		// Set maze end to red.
		g2d.setColor(Color.red);
		g2d.fillRect(maze.getEndCell().getPosY() * cellSize, maze.getEndCell().getPosX() * cellSize, cellSize, cellSize);
		
		repaint();
	}
	
	public void addSolution(final LinkedList<MazeCell> mazeSolution)
	{
		g2d.setColor(Color.yellow);
		g2d.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, 0.35f));
		final Timer timer = new Timer(50, null);
		final Iterator<MazeCell> it = mazeSolution.iterator();
		ActionListener drawCell = new ActionListener() 
		{
			@Override
			public void actionPerformed(ActionEvent e) 
			{
				MazeCell cell = it.next();
				g2d.fillRect(cell.getPosY() * cellSize, cell.getPosX() * cellSize, cellSize, cellSize);
				repaint();
				if (!it.hasNext()) timer.stop();
			}
		};
		
		timer.addActionListener(drawCell);
		timer.start();
	}
	
	public void addFullPath(final LinkedList<MazeCell> fullPath)
	{
		g2d.setColor(Color.red);
		g2d.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, 0.5f));
		final int ovalOffset = this.cellSize / 4;
		final int ovalRadius = this.cellSize / 2;
		final Timer timer = new Timer(50, null);
		final Iterator<MazeCell> it = fullPath.iterator();
		ActionListener drawCell = new ActionListener() 
		{
			@Override
			public void actionPerformed(ActionEvent e) 
			{
				MazeCell cell = it.next();
				g2d.fillOval(cell.getPosY() * cellSize + ovalOffset, cell.getPosX() * cellSize + ovalOffset, ovalRadius, ovalRadius);
				repaint();
				if (!it.hasNext()) timer.stop();
			}
		};
		
		timer.addActionListener(drawCell);
		timer.start();
	}

	public void clear()
	{
		createEmptyImage();
		repaint();
	}
}
