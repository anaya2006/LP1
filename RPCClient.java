import java.io.*;
import java.net.*;

public class RPCClient {
    public static void main(String[] args) throws IOException {
        BufferedReader console = new BufferedReader(new InputStreamReader(System.in));

        Socket socket = new Socket("localhost", 5000);
        PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));

        System.out.println("----- MENU -----");
        System.out.println("1. Logarithm");
        System.out.println("2. Log Add");
        System.out.println("3. Log Subtract");
        System.out.println("4. Log Multiply");
        System.out.println("5. Log Divide");
        System.out.print("Enter your choice: ");
        int choice = Integer.parseInt(console.readLine());

        out.println(choice);

        System.out.print("Enter first number: ");
        double num1 = Double.parseDouble(console.readLine());
        out.println(num1);

        if (choice != 1) {
            System.out.print("Enter second number: ");
            double num2 = Double.parseDouble(console.readLine());
            out.println(num2);
        }

        String response = in.readLine();
        System.out.println("Server Response: " + response);

        socket.close();
    }
}
