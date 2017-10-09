package gui;

import javax.swing.*;

/**
 * Created by Michał on 2015-02-22.
 */
public class ServerExceptionHandler implements Thread.UncaughtExceptionHandler {
    @Override
    public void uncaughtException(Thread t, Throwable e) {
        JOptionPane.showMessageDialog(null,e.toString(),"Error occured",JOptionPane.ERROR_MESSAGE);

    }
}
