package BoardPackage;
import java.io.Serializable;
import java.util.LinkedList;

public class Board implements Serializable {
	private static final long serialVersionUID = -8983947526345382477L;
	private BoardCell[][] board;
	private int height;
	private int width;
	
	
	public Board (int height, int width)
	{
		this.height = height;
		this.width = width;
		board = new BoardCell[height][width];
		
		for (int h = 0; h < height; h++)
		{
			for (int w = 0; w < width; w++)
			{
				board[h][w] = new BoardCell(h, w);
			}
		}
	}
	
	public Board (Board original)
	{
		this(original.height, original.width);
		
		for (int h = 0; h < this.height; h++)
		{
			for (int w = 0; w < this.width; w++)
			{
				this.board[h][w] = original.board[h][w];
			}
		}
	}
	
	/**
	 * 
	 * @return
	 */
	public int getWidth()
	{
		return width;
	}
	
	/**
	 * 
	 * @return
	 */
	public int getHeight()
	{
		return height;
	}
	
	/**
	 * 
	 * @param x
	 * @param y
	 * @return
	 */
	public BoardCell getCell(int x, int y)
	{
		return board[x][y];
	}
	
	/**
	 * 
	 * @param x
	 * @param y
	 * @return
	 */
	public boolean checkCell(int x, int y)
	{
		if (!board[x][y].isEmpty())
			return true;
		else 
			return false;
	}
	
	/**
	 * 
	 * @param x
	 * @param y
	 * @param c
	 */
	public void setCell(int x, int y, BoardCell c)
	{
		if (!board[x][y].isEmpty())
		{
			c.setHorizontal(board[x][y].getHorizontal());
			c.setVertical(board[x][y].getVertical());
		}
		
		board[x][y] = c;
	}
	
	/**
	 * 
	 * @return
	 */
	public LinkedList<BoardCell> getStartCells()
	{
		LinkedList<BoardCell> results = new LinkedList<BoardCell>();
		
		for (int h = 0; h < this.height; h++)
		{
			for (int w = 0; w < this.width; w++)
			{
				if (!board[h][w].isEmpty() && (board[h][w].getHorizontal().get(0) || board[h][w].getVertical().get(0)))
						results.add(board[h][w]);
			}
		}
		return results;
	}
	
	/**
	 * 
	 * @param fromx
	 * @param fromy
	 * @param tox
	 * @param toy
	 * @return
	 */
	public String createPattern (int fromx, int fromy, int tox, int toy)
	{
		StringBuilder sb = new StringBuilder("(?i)^");
		
		for (int x = fromx; x <= tox; x++)
		{
			for (int y = fromy; y <= toy; y++)
			{
				if (!board[x][y].isEmpty())
					sb.append(board[x][y]);
				else
					sb.append(".?");	
			}
		}
		sb.append("$");
		
		return sb.toString();
	}
	
	@Override
	public String toString()
	{
		StringBuilder sb = new StringBuilder();
		for (int h = 0; h < this.height; h++)
		{
			for (int w = 0; w < this.width; w++)
			{
				if (!board[h][w].isEmpty())
					sb.append(board[h][w].getContent());
				else
					sb.append("   ");
			}
			sb.append("\n");
		}
		return sb.toString();
	}
}
