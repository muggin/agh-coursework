package visca;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by O10 on 06.12.2015.
 */
public class ViscaServer {
    private Thread serverThread;
    private ViscaDeviceSession deviceSession;

    public void start(ViscaDeviceSession deviceSession) {
        this.deviceSession = deviceSession;
        serverThread = new Thread(new ServerRunnable());
        serverThread.start();
    }

    public class ViscaHandler implements HttpHandler {

        public void handle(HttpExchange httpExchange) throws IOException {
            Map<String, String> params = null;
            try {
                params = queryToMap(httpExchange.getRequestURI().getQuery());
                System.out.println("Handling web client request" + " Request parameters: " + params);
            } catch (Exception e) {
                e.printStackTrace();
            }

            String response;
            String viscaCommand;

            if (params == null || (viscaCommand = params.get("command")) == null) {
                response = "Command not specified";
                httpExchange.sendResponseHeaders(200, response.length());
                OutputStream os = httpExchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
                return;
            }

            viscaCommand = viscaCommand.replace("+", " ");
            String[] splitTokens = viscaCommand.split(" ");

            ViscaDeviceSession.Command[] commands = ViscaController.getCommandsFromInputToken(splitTokens);

            if (splitTokens[0].equalsIgnoreCase("DM")) {
                deviceSession.defineMacro(commands);
            } else {
                deviceSession.sendCommands(commands);
            }
            httpExchange.getResponseHeaders().add("Access-Control-Allow-Origin", "*");
            httpExchange.sendResponseHeaders(200, viscaCommand.length());
            OutputStream os = httpExchange.getResponseBody();
            os.write(viscaCommand.getBytes());
            os.close();
        }
    }

    public class ServerRunnable implements Runnable {

        public void run() {
            HttpServer server = null;
            try {
                server = HttpServer.create(new InetSocketAddress(8000), 0);
            } catch (IOException e) {
                e.printStackTrace();
                System.out.println("Error while creating the server.");
                return;
            }
            server.createContext("/", new ViscaHandler());
            server.setExecutor(null); // creates a default executor
            server.start();
        }
    }

    public static Map<String, String> queryToMap(String query) {
        Map<String, String> result = new HashMap<String, String>();
        for (String param : query.split("&")) {
            String pair[] = param.split("=");
            if (pair.length > 1) {
                result.put(pair[0], pair[1]);
            } else {
                result.put(pair[0], "");
            }
        }
        return result;
    }
}
