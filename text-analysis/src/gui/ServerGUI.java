package gui;

import model.chunks.FileChunk;
import node.interfaces.MRNode;
import server.ConnectionHandler;
import server.interfaces.ServerObserver;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

/**
 * Created by Michał on 2015-02-19.
 */
public class ServerGUI extends JFrame implements ServerObserver{


    private JPanel rootServerPanel;
    private JButton STARTSERVERButton;
    private JButton searchFileButton;
    private JFormattedTextField chooseFileInputField;
    private JFormattedTextField attachedNodesInputField;

    private JLabel ServerLabel;
    private JButton runBtn;
    private ConnectionHandler connectionServer;
    private File textFile;
    private ArrayList<FileChunk> fc;

    public ServerGUI(){
        final ServerGUI refernce=this;
        ServerLabel.setFont(new Font(ServerLabel.getFont().getFontName(), Font.BOLD, 20));
        chooseFileInputField.setFont(new Font(chooseFileInputField.getFont().getFontName(), Font.ITALIC, chooseFileInputField.getFont().getSize()));
        searchFileButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser fileChooser = new JFileChooser(".");
                fileChooser.setDialogTitle("Specify a file to save");
                int result = fileChooser.showOpenDialog(new JFrame());
                if(result == JFileChooser.APPROVE_OPTION) {
                    File selectedFile = fileChooser.getSelectedFile();
                    chooseFileInputField.setText(selectedFile.getName());
                    textFile=selectedFile.getAbsoluteFile();
                    STARTSERVERButton.setEnabled(true);
                }
                else {
                    chooseFileInputField.setText("NO FILE SELECTED");
                }
            }
        });

        STARTSERVERButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    if(textFile==null||!textFile.exists())
                        throw new Exception("File validation failed!");
                    RunCommand.init(refernce);
                } catch (Exception e1) {
                    //pass to default handler
                    throw new RuntimeException(e1);
                }
                //success
                STARTSERVERButton.setEnabled(false);
                searchFileButton.setEnabled(false);
            }
        });
        runBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    RunCommand.exec(textFile.getAbsolutePath());
                } catch (IOException e1) {
                    //pass to default handler
                    throw new RuntimeException(e1);
                }
            }
        });
    }

    public static void main(String[] args) {
        Thread.setDefaultUncaughtExceptionHandler(new ServerExceptionHandler());
        JFrame frame = new JFrame("ServerGUI");
        frame.setContentPane(new ServerGUI().rootServerPanel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        //frame.pack();
        frame.setSize(700, 300);
        frame.setVisible(true);
    }

    public String getChoosenFile() {
        return (String) chooseFileInputField.getText();
    }

    @Override
    public void update(MRNode node) {
        /**
         * Metoda z interfejsu obserwatora
         * Nasłuchuje na event node register
         * i aktualizuje ilość podłączonych nodów
         */
        if(RunCommand.lb!=null) {

            if(RunCommand.lb.nodeCount()>0) {
                runBtn.setEnabled(true);
                attachedNodesInputField.setText(String.valueOf(RunCommand.lb.nodeCount()));
            }
            else {
                runBtn.setEnabled(false);
                attachedNodesInputField.setText("Waiting for connections...");
            }
        }
    }
}
