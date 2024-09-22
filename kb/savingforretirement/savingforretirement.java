/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/savingforretirement
TAGS: brute force, math
EXPLANATION:
try every possible age, use math to figure out how much money each will have after a given amount of time.
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.StringReader;
import java.util.StringTokenizer;
 
public class savingforretirement {
    
    //this is used for actual solution output. It is very fast but will not show up on the console until the run() method terminates (or until you call pout.flush()).
    PrintWriter pout;
    
    //this is used for timing your code
    long startTimeMillis;
    long benchmark;
    
    //set this to false to remove all debug and timing output for submission.
    boolean DEBUG_FLAG = true;
    
    //this is just the entry point of your program. 
    //it will instantiate an instance of your solution class, set it's relevent variables, and then call its run() method to do the solving.
    //this also prints all output in pout's buffer for you after run() is complete.
    public static void main(String[] args) throws Exception
    {
        long entryTime = System.currentTimeMillis();
        savingforretirement t = new savingforretirement();
        t.benchmark = t.startTimeMillis = entryTime;
        t.pout = new PrintWriter(System.out);
        t.run();
        t.pout.flush();
        t.pout.close();
    }   
    
    //solution code goes here
    public void run() throws Exception
    {
        Scanner file = new Scanner(System.in);
        int B = file.nextInt();
        int Br = file.nextInt();
        int Bs = file.nextInt();
        int A = file.nextInt();
        int As = file.nextInt();
        int current = A;
        int BSaved = Bs*(Br - B);
        while(true)
        {
            int amt = As*(current - A);
            if(amt > BSaved)
            {
                System.out.println(current);
                return;
            }
            current++;
        }
    }
    
    //prints out o if DEBUG_FLAG is true, does nothing otherwise
    //If you use pout for all real output and print() for all debugging output, you won't have to run through your code deleting prints after you get your solution working. 
    //Instead you can just set DEBUG_FLAG to false;
    public void print(Object o)
    {
        if(DEBUG_FLAG)
            System.out.println(o);
    }
    
    //call time to print a debug of how long a certain segment of your code has taken in milliseconds.
    //does nothing if DEBUG_FLAG is false
    public void time(String s)
    {
        if(DEBUG_FLAG)
        {
            long time = System.currentTimeMillis();
            System.out.println(s+": "+(time - startTimeMillis)+" ("+(time - benchmark)+" millis from last benchmark)");
            benchmark = time;
        }
    }
    
    //A fast bare-bones implementation of java.util.Scanner for fast input
    private class Scanner 
    { 
        BufferedReader br; 
        StringTokenizer st; 
  
        public Scanner() 
        { 
            this(System.in);
        } 
        
        public Scanner(File f) throws FileNotFoundException
        {
            br = new BufferedReader(new FileReader(f));
        }
        
        public Scanner(InputStream is)
        {
            br = new BufferedReader(new
                    InputStreamReader(is)); 
        }
        
        public Scanner(String content)
        {
            br = new BufferedReader(new StringReader(content));
        }
  
        String next() 
        { 
            while (st == null || !st.hasMoreElements()) 
            { 
                try
                { 
                    st = new StringTokenizer(br.readLine()); 
                } 
                catch (IOException  e) 
                { 
                    e.printStackTrace(); 
                } 
            } 
            return st.nextToken(); 
        } 
  
        int nextInt() 
        { 
            return Integer.parseInt(next()); 
        } 
  
        long nextLong() 
        { 
            return Long.parseLong(next()); 
        } 
  
        double nextDouble() 
        { 
            return Double.parseDouble(next()); 
        } 
  
        String nextLine() 
        { 
            try {
                return st.nextToken("");
            }catch(Exception ex) {
                String str = ""; 
                try
                { 
                    str = br.readLine(); 
                } 
                catch (IOException e) 
                { 
                    e.printStackTrace(); 
                } 
                return str; 
            }
        } 
    }
    
}