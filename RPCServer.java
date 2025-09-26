import java.io.*;
import java.net.*;

public class RPCServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(5000);
        System.out.println("RPC Log Server started. Listening on port 5000...");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            System.out.println("Client connected.");

            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);

            int choice = Integer.parseInt(in.readLine());
            double num1 = Double.parseDouble(in.readLine());
            double num2 = 0.0;

            if (choice != 1) {  // only for subtraction, multiplication, division we need 2 inputs
                num2 = Double.parseDouble(in.readLine());
            }

            double result = 0.0;
            try {
                switch (choice) {
                    case 1: // Logarithm
                        result = Math.log(num1);
                        break;
                    case 2: // Log Add
                        result = Math.log(num1) + Math.log(num2);
                        break;
                    case 3: // Log Sub
                        result = Math.log(num1) - Math.log(num2);
                        break;
                    case 4: // Log Multiply
                        result = Math.log(num1) * Math.log(num2);
                        break;
                    case 5: // Log Divide
                        result = Math.log(num1) / Math.log(num2);
                        break;
                    default:
                        out.println("Invalid choice!");
                        clientSocket.close();
                        continue;
                }
                out.println("Result: " + result);
            } catch (Exception e) {
                out.println("Error: " + e.getMessage());
            }

            clientSocket.close();
        }
    }
}
