import java.net.Socket;
import java.util.Scanner;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;



public class Client
{
   public static void main (String[] args)
   {
      Socket socket =null;
      BufferedReader bufferedreader =null;
      BufferedWriter bufferedwriter =null;
      InputStreamReader inputstreamreader =null;
      OutputStreamWriter outputstreamreader =null;
      
         try 
      {  
         socket = new Socket(host: "localhost" , port: 1234);
         inputstreamreader = new InputStreamReader(socket.GetInputStream());
         outputstreamreader = new OutputStreamReader(socket.GetOutputStream());
         Scanner s = new Scanner(System.in);
         
         
         while (true)
         {
           String msg = s.nextline();
           bufferedwriter.write(msg);
           bufferedwriter.newline();
           bufferedwriter.flush();
           
           System.out.println("SERVER : "+bufferedwriter.readline());
           
           if (equalsIgnoreCase(anotherString: "EXIT"))
              break;
         }
      
      }
      
      catch (IOexception e)
      {
        e.printStackTrace();
      }
   
     finally 
     {
        try 
        {
           if (socket!= null)
              socket.close();
              
           if (bufferedreader != null)
               bufferedreader.close();
               
           if (bufferedwriter != null)
               bufferedwriter.close();
               
           if (inputstreamreader != null)
               inputstreamreader.close(); 
        
           if (outputstreamwriter !=null)
              outputstreamwriter.close();
        
        }
             catch (IOexception e)
          {
             e.printStackTrace();
          }
  
     }
   }


}
