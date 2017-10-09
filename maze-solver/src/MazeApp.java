import java.awt.BorderLayout;
import java.awt.FlowLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.InputStream;



public class MazeApp {
	private JFrame frame;
	private Robot mazeSolver;
	private Maze maze;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					MazeApp window = new MazeApp();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public MazeApp() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() 
	{
		setupLogic(this.getClass().getResourceAsStream("labirynt.txt"));
		setupGUI();
	}
	
	private void setupLogic(InputStream inputStream)
	{
		maze = new Maze(inputStream);
		mazeSolver = new Robot(maze);
		mazeSolver.solveMaze();
	}
	
	private void setupGUI()
	{
		frame = new JFrame();
		frame.setBounds(100, 100, 600, 400);
		System.out.println(frame.getSize());
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setLayout(new BorderLayout());
		frame.setResizable(false);
		
		final DrawingCanvas panel = new DrawingCanvas(this.maze.getSizeX(), this.maze.getSizeY());
		frame.getContentPane().add(panel, BorderLayout.CENTER);
		
		final JPanel southPanel = new JPanel();
		southPanel.setLayout(new BorderLayout());
		frame.getContentPane().add(southPanel, BorderLayout.SOUTH);
		
		final JPanel lblPanel = new JPanel();
		lblPanel.setLayout(new FlowLayout());
		southPanel.add(lblPanel, BorderLayout.WEST);
		
		final JLabel stepCountLabel = new JLabel("Path length: ");
		lblPanel.add(stepCountLabel);
		final JLabel stepCount = new JLabel();
		lblPanel.add(stepCount);
		
		final JPanel bttnPanel = new JPanel();
		bttnPanel.setLayout(new FlowLayout());
		southPanel.add(bttnPanel, BorderLayout.EAST);
		
		final JButton showMazeBttn = new JButton("Show Maze");
		showMazeBttn.addActionListener(new ActionListener() 
		{
			@Override
			public void actionPerformed(ActionEvent e) 
			{
				panel.addMaze(maze);
			}
		});
		bttnPanel.add(showMazeBttn);
		
		final JButton solveMazeBttn = new JButton("Solve Maze");
		solveMazeBttn.addActionListener(new ActionListener() 
		{
			@Override
			public void actionPerformed(ActionEvent e) 
			{
				
				panel.addSolution(mazeSolver.getMazeSolution());
				stepCount.setText(Integer.toString(mazeSolver.getMazeSolution().size()));
			}
		});
		bttnPanel.add(solveMazeBttn);
	}
		

}
