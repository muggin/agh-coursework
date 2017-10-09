package visca;

import jssc.SerialPort;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;
import jssc.SerialPortException;

import javax.xml.bind.DatatypeConverter;
import java.util.ArrayList;
import java.util.EnumMap;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

/**
 * Created by Wojtek on 03/12/15.
 */
public class ViscaDeviceSession implements Runnable {
    private static EnumMap<Command, String> rawCommandMapping;
    private final SerialPort serialPort;
    private final BlockingQueue<Command> commandQueue;
    private Command[] definedMacro;

    // Mapping from Command enum to hex Command strings
    static {
        ViscaDeviceSession.rawCommandMapping = new EnumMap<Command, String>(Command.class);
        rawCommandMapping.put(Command.CLEAR_ALL, "88010001FF");
        rawCommandMapping.put(Command.AUTO_ADDR_ASSGN, "883001FF");
        rawCommandMapping.put(Command.PWR_ON, "8101040002FF");
        rawCommandMapping.put(Command.PWR_OFF, "8101040003FF");
        rawCommandMapping.put(Command.PAN_LEFT, "8101060106060103FF");
        rawCommandMapping.put(Command.PAN_RIGHT, "8101060106060203FF");
        rawCommandMapping.put(Command.TILT_UP, "8101060106060301FF");
        rawCommandMapping.put(Command.TILT_DOWN, "8101060106060302FF");
        rawCommandMapping.put(Command.ZOOM_IN, "");
        rawCommandMapping.put(Command.ZOOM_OUT, "");
    }

    public ViscaDeviceSession(String portName) throws SerialPortException {
        this.commandQueue = new LinkedBlockingQueue<Command>();
        this.serialPort = new SerialPort(portName);
        this.serialPort.openPort();
        this.serialPort.setParams(9600, 8, 1, 0);
        this.serialPort.addEventListener(new SerialPortEventListener() {
            public void serialEvent(SerialPortEvent serialPortEvent) {
                try {
                    String msg = serialPort.readHexString(serialPortEvent.getEventValue());
                    System.out.println("Serial received: " + msg);
                } catch (SerialPortException e) {
                    e.printStackTrace();
                }
            }
        }, SerialPort.MASK_RXCHAR);
    }

    // Send single command
    public void sendCommand(Command command) {
        if (command == Command.MACRO && definedMacro != null) {
            for (Command macroCommand : definedMacro) {
                commandQueue.add(macroCommand);
            }
        } else {
            commandQueue.add(command);
        }
    }

    // Send array of commands
    public void sendCommands(Command[] commands) {
        for (Command command : commands) {
            sendCommand(command);
        }
    }

    // Define macro
    public void defineMacro(Command[] macroCommands) {
        ArrayList<Command> filteredMacro = new ArrayList<Command>();

        for (Command command : macroCommands) {
            if (command != Command.MACRO && command != Command.CLEAR_ALL && command != Command.AUTO_ADDR_ASSGN) {
                filteredMacro.add(command);
            }
        }

        this.definedMacro = filteredMacro.toArray(new Command[filteredMacro.size()]);
    }

    public enum Command {
        CLEAR_ALL, AUTO_ADDR_ASSGN, PWR_ON, PWR_OFF, PAN_LEFT, PAN_RIGHT, TILT_UP, TILT_DOWN, ZOOM_IN, ZOOM_OUT, WAIT, MACRO
    }

    public void run() {
        while (true) {
            try {
                Command nextCommand = commandQueue.take();
                System.out.println("Received command: " + nextCommand);
                if (nextCommand == Command.WAIT) {
                    Thread.sleep(2000);
                } else {
                    String rawCommand = rawCommandMapping.get(nextCommand);
                    byte[] binaryCommand = DatatypeConverter.parseHexBinary(rawCommand);
                    serialPort.writeBytes(binaryCommand);
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            } catch (SerialPortException e) {
                e.printStackTrace();
            }
        }
    }
}
