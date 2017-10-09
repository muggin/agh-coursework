package gui;

import node.Node;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.Registry;

/**
 * Created by Michał on 2015-02-21.
 */
public class NodeGUI extends JFrame {
    private JLabel NodeTitleLabel;
    private JLabel IPLabel;
    private JFormattedTextField IPField;
    private JLabel PortLabel;
    private JFormattedTextField PortField;
    private JLabel ThreadLimitLabel;
    private JComboBox ThreadLimitcomboBox;
    private JPanel rootNodePanel;
    private JButton CONNECTButton;
    private JFormattedTextField ChooseDirField;
    private JLabel ChooseDirLabel;
    private JButton ChooseDirButton;

    private Node node;
    private File tempDir;

    public NodeGUI() {

        IPField.setText("localhost");
        PortField.setText(String.valueOf(Registry.REGISTRY_PORT));

        NodeTitleLabel.setFont(new Font(NodeTitleLabel.getFont().getFontName(), Font.BOLD, 18));

        ThreadLimitcomboBox.setFont(new Font(ThreadLimitcomboBox.getFont().getFontName(), Font.ITALIC, ThreadLimitcomboBox.getFont().getSize()));
        ThreadLimitcomboBox.addItem("Select number of threads");
            for(int i=0; i < 10; i++) {
                ThreadLimitcomboBox.addItem(i);
            }

        ChooseDirField.setFont(new Font(ChooseDirField.getFont().getFontName(), Font.ITALIC, ChooseDirField.getFont().getSize()));
        ChooseDirButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser fileChooser = new JFileChooser(".");
                fileChooser.setDialogTitle("Specify a file to save");
                fileChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
                fileChooser.setAcceptAllFileFilterUsed(false);
                int result = fileChooser.showOpenDialog(new JFrame());
                if(result == JFileChooser.APPROVE_OPTION) {
                    File selectedFile = fileChooser.getSelectedFile();
                    ChooseDirField.setText(selectedFile.getName());
                    tempDir=selectedFile.getAbsoluteFile();
                }
                else {
                    ChooseDirField.setText("NO FILE SELECTED");
                }
            }
        });

        CONNECTButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(IPField.getText().isEmpty()||PortField.getText().isEmpty())
                    throw new RuntimeException("Fix host/port field");
                if(tempDir==null || !tempDir.exists() || !tempDir.isDirectory())
                    throw new RuntimeException("Please select valid temp dir");
                try {
                    node=new Node(IPField.getText(), tempDir.getAbsolutePath(), 5);
                    node.registerNode();
                } catch (RemoteException|NotBoundException e1) {
                    new RuntimeException("Error during connect: "+ e1.toString());
                }

                //success
                CONNECTButton.setEnabled(false);
                IPField.setEnabled(false);
                PortField.setEnabled(false);
            }
        });
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("NodeGUI");
        frame.setContentPane(new NodeGUI().rootNodePanel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        //frame.pack();
        frame.setSize(500, 300);
        frame.setVisible(true);
    }

}
