import java.io.*;
import java.util.*;

class header
{   
    // load library
    static 
    {
      System.loadLibrary("source");
    }
    
    //call native methods
    private native int add(int a, int b);
    private native int sub(int a, int b);
    private native int mult(int a, int b);
    private native float div(int a, int b);
    
  public static void main (String[] args)
  {
      int a,b,ch;
      Scanner sc= new Scanner(System.in);
      System.out.println("Enter value of a :");
      a= sc.nextInt();
      System.out.println("Enter value of b :");
      b= sc.nextInt();
      
     do
      {
          System.out.println("MENU");
          System.out.println("1. Add \n 2. Subtract \n 3. Multiply \n 4. Divide ");
          System.out.println("Enter a choice : ");
          ch=sc.nextInt();
          
          switch (ch) 
          {
             case 1 : 
               new header().add(a,b);
               break;
               
             case 2 : 
               new header().sub(a,b);
               break;
          
             case 3 : 
               new header().mult(a,b);
               break;
               
             case 4 : 
               new header().div(a,b);
               break;
               
             default:
                System.out.println("Invalid option selected, please enter a valid option ");
          
          }
          
        } while(ch<5);
        
      }
 
   }
   

