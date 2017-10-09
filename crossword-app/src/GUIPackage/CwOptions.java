package GUIPackage;

import java.awt.GridLayout;

import javax.swing.BorderFactory;
import javax.swing.ButtonGroup;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;
import javax.swing.SwingConstants;

public class CwOptions extends JPanel {
	private static final long serialVersionUID = -1632557481155397630L;
	private String gameStrategy;
	private Integer heightSet, widthSet, heightMin, heightMax, widthMin, widthMax;
	private JTextField heightField, widthField;
	private ButtonGroup btnGroup;
	JLabel heightLabel, widthLabel, simpleLabel, advancedLabel, heightLimit, widthLimit;
	JPanel dimensionPanel, strategyPanel;
	JRadioButton simpleButton, advancedButton;
	JOptionPane optionPane;
     
     CwOptions(int heightMin, int heightMax, int widthMin, int widthMax)
     {
    	 this.heightMin = heightMin;
    	 this.heightMax = heightMax;
    	 this.widthMin = widthMin;
    	 this.widthMax = widthMax;
    	 initOptions();
    	 initDimensionPanel();
    	 initStrategyPanel();
     }
     
     /**
      * Funkcja inicjalizuje i ustawia glowne okno opcji.
      */
     private void initOptions()
     {
    	 setLayout(new GridLayout(2, 1));
     }
     
     /**
      * Funkcja inicjalizuje i ustawia panel ustawien rozmiaru.
      */
     private void initDimensionPanel()
     {
    	 dimensionPanel = new JPanel();
    	 dimensionPanel.setBorder(BorderFactory.createTitledBorder("Dimension settings"));
    	 dimensionPanel.setLayout(new GridLayout(2,3));
    	 heightLabel = new JLabel("Crossword height: ", SwingConstants.RIGHT);
    	 heightField = new JTextField(2);
    	 heightField.setHorizontalAlignment(SwingConstants.CENTER);
    	 heightLimit = new JLabel("[" + heightMin + "-" + heightMax + "]", SwingConstants.LEFT);
    	 widthLabel = new JLabel("Crossword width: ", SwingConstants.RIGHT);
    	 widthField = new JTextField(2);
    	 widthField.setHorizontalAlignment(SwingConstants.CENTER);
    	 widthLimit = new JLabel("[" + heightMin + "-" + heightMax + "]", SwingConstants.LEFT);
    	 dimensionPanel.add(heightLabel);
    	 dimensionPanel.add(heightField);
    	 dimensionPanel.add(heightLimit);
    	 dimensionPanel.add(widthLabel);
    	 dimensionPanel.add(widthField);
    	 dimensionPanel.add(widthLimit);
    	
    	 add(dimensionPanel);
     }
     
     /**
      * Funkcja inicjalizuje i ustawia panel ustawien strategii gry.
      */
     private void initStrategyPanel()
     {
    	 strategyPanel = new JPanel();
    	 strategyPanel.setBorder(BorderFactory.createTitledBorder("Strategy settings"));
    	 strategyPanel.setLayout(new GridLayout(2, 2));
    	 btnGroup = new ButtonGroup();
    	 simpleLabel = new JLabel("Simple strategy: ", SwingConstants.RIGHT);
    	 simpleButton = new JRadioButton();
    	 btnGroup.add(simpleButton);
    	 simpleButton.setHorizontalAlignment(SwingConstants.CENTER);
    	 simpleButton.setActionCommand("SimpleStrategy");
    	 advancedLabel = new JLabel("Advanced strategy: ", SwingConstants.RIGHT);
    	 advancedButton = new JRadioButton();
    	 advancedButton.setActionCommand("AdvancedStrategy");
    	 btnGroup.add(advancedButton);
    	 advancedButton.setHorizontalAlignment(SwingConstants.CENTER);
    	 strategyPanel.add(simpleLabel);
    	 strategyPanel.add(simpleButton);
    	 strategyPanel.add(advancedLabel);
    	 strategyPanel.add(advancedButton);
    	 strategyPanel.setVisible(true);
    	 
    	 add(strategyPanel);
     }
     
     /**
      * Funkcja wyswietla panel opcji.
      * @param currentHeight - aktualna wysokosc planszy.
      * @param currentWidth - aktualna szerokosc planszy.
      */
     public void openOptions(int currentHeight, int currentWidth, String gStrategy)
     {
    	 heightField.setText(Integer.toString(currentHeight));
    	 widthField.setText(Integer.toString(currentWidth));
    	 btnGroup.clearSelection();
    	 this.gameStrategy = gStrategy;
    	 
    	 if (gameStrategy.equals("SimpleStrategy"))
    		 simpleButton.setSelected(true);
    	 else
    		 advancedButton.setSelected(true);
    	 
    	 int result = JOptionPane.showConfirmDialog(this, this, "Crossword Options", JOptionPane.OK_CANCEL_OPTION);
    	 
    	 if (result == JOptionPane.OK_OPTION) 
    	 {
    		 String hField = heightField.getText();
    		 String wField = widthField.getText();
    		 
    		 if(!hField.matches("\\d+") || !wField.matches("\\d+") || hField.isEmpty() || wField.isEmpty())
     	    {
    			JOptionPane.showMessageDialog(null, "Invalid input.", "Input error.", JOptionPane.OK_OPTION);
     	        openOptions(currentHeight, currentWidth, gStrategy);
     	    }
    		 
    		 heightSet = Integer.parseInt(heightField.getText());
    		 widthSet = Integer.parseInt(widthField.getText());
    		 if (simpleButton.isSelected())
    			 this.gameStrategy = simpleButton.getActionCommand();
    		 else
    			 this.gameStrategy = advancedButton.getActionCommand();
    		 
    		 
    		 if (heightSet > heightMax || heightSet < heightMin || widthSet > widthMax || widthSet < widthMin)
    		 {
     			JOptionPane.showMessageDialog(null, "Input out of range.", "Input error.", JOptionPane.OK_OPTION);
     	        openOptions(currentHeight, currentWidth,  gStrategy);
    		 }
    	 }
    	 else
    	 {
    		 heightSet = currentHeight;
    		 widthSet = currentWidth;
    		 
    	 }
     }
     
     /**
      * Funkcja zwraca aktualne ustawienia wysokosci planszy.
      * @return - ustawienia wysokosci planszy.
      */
     public int getHeightSet() 
     {
		return heightSet;
     }

     /**
      * Funkcja zwraca aktualne ustawienia szerokosci planszy.
      * @return ustawienia szerokosci planszy.
      */
     public int getWidthSet() 
     {
		return widthSet;
     }
     
     public String getGameStrategy()
     {
    	 return gameStrategy;
     }
}
