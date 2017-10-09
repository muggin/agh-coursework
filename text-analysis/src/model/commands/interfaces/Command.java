package model.commands.interfaces;

import java.io.Serializable;

/**
 * Created by Wojtek on 18/02/15.
 * Interfejs implementujący wzorzec Command Pattern.
 */
public interface Command extends Serializable {
    /**
     * Metoda przygotowująca do kroku głównego.
     * @param outputSetup
     */
    public void preExecution(String outputSetup);

    /**
     *
     */
    public void execute();

    /**
     *
     */
    public void postExecution();
}
