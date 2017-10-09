package visca;

import jssc.SerialPortException;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

import static visca.ViscaDeviceSession.Command;

/**
 * Created by Wojtek on 03/12/15.
 */
public class ViscaController {
    static private final HashMap<String, Command> inputToCommands;

    static {
        inputToCommands = new HashMap<String, Command>();
        inputToCommands.put("PON", Command.PWR_ON);
        inputToCommands.put("POFF", Command.PWR_OFF);
        inputToCommands.put("L", Command.PAN_LEFT);
        inputToCommands.put("R", ViscaDeviceSession.Command.PAN_RIGHT);
        inputToCommands.put("U", ViscaDeviceSession.Command.TILT_UP);
        inputToCommands.put("D", ViscaDeviceSession.Command.TILT_DOWN);
        inputToCommands.put("W", ViscaDeviceSession.Command.WAIT);
        inputToCommands.put("M", ViscaDeviceSession.Command.MACRO);
    }

    // Translate input tokens to Command enums.
    static public Command[] getCommandsFromInputToken(String[] inputTokens) {
        ArrayList<Command> commandList = new ArrayList<Command>();
        for (String token : inputTokens) {
            Command nextCommand = ViscaController.inputToCommands.get(token.toUpperCase());

            if (nextCommand != null) {
                commandList.add(nextCommand);
            }
        }

        return commandList.toArray(new Command[commandList.size()]);
    }

    public static void main(String[] argv) {
        String serialPort = "COM1";
        boolean shouldStartServer = false; //set to true to allow client to connect

        if (argv.length > 0 && argv[0].matches("COM[1-3]")) {
            serialPort = argv[0];
        }

        if (argv.length > 0 && argv[1].matches("server")) {
            shouldStartServer = true;
        }

        try {
            System.out.println("Setting up serial port connection on port: " + serialPort);
            ViscaDeviceSession deviceSession = new ViscaDeviceSession(serialPort);
            Thread sessionThread = new Thread(deviceSession);
            sessionThread.start();
            System.out.println("Setting up VISCA device");
            deviceSession.sendCommand(Command.CLEAR_ALL);
            deviceSession.sendCommand(Command.AUTO_ADDR_ASSGN);

            if (shouldStartServer) {
                System.out.println("Starting HTTP server");
                ViscaServer viscaServer = new ViscaServer();
                viscaServer.start(deviceSession);
            }

            System.out.print("Enter VISCA commands:\n>");
            Scanner userInput = new Scanner(System.in);
            while (userInput.hasNext()) {
                System.out.print("> ");
                String nextToken = userInput.nextLine();
                String[] splitTokens = nextToken.split(" ");

                Command[] commands = ViscaController.getCommandsFromInputToken(splitTokens);

                if (splitTokens[0].equalsIgnoreCase("DM")) {
                    deviceSession.defineMacro(commands);
                } else {
                    deviceSession.sendCommands(commands);
                }
                System.out.println(nextToken);
            }

        } catch (SerialPortException e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }
}

// Example commandline input
// dm l r l r w u d <- defines macro left right left right wait up down
// m <- use macro
// u d <- up down
