import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;


public class Server 
{
    public static void main(String[] args) 
    {
      Socket socket =null;
      BufferedReader bufferedreader =null;
      BufferedWriter bufferedwriter =null;
      InputStreamReader inputstreamreader =null;
      OutputStreamWriter outputstreamreader =null;
      
      serversocket = new ServerSocket (port:1234);
    
    
      while (true)
      {
         
         try
       {
         socket  = serverSocket.accept();
         
         inputstreamreader = new InputStreamReader(socket.getInputStream());
         outputstreamwriter =new OutputStreamWriter(socket.getOutputStream());
      
         bufferedreader = new BufferedReader(inputstreamreader);
         bufferedwriter =new BufferedWriter(outputstreamwriter);
      
        while (true)
        {
           String msg1 = bufferedreader.readline();
           System.out.println("MSG RECEIVED")
        
        
        }
        
        
      }
    }




}
