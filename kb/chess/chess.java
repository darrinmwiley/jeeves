/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/chess
TAGS: math, casework
EXPLANATION:
you can move from a to b if (r+c) or (r-c) are same
for any square one of three cases is true
1) impossible (r+c) are two different parity
2) one move
3) one intermediary move
handle each case accordingly
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.HashSet;
import java.util.StringTokenizer;
 
public class chess {
    
    StringTokenizer st;
    BufferedReader file;
    
    public static void main(String[] args) throws Exception
    {
        new chess().run();
    }
    
    String position = "HGFEDCBA";
    
    public void run() throws Exception
    {
        
        //this is fast IO - faster than Scanner/System.out.println
        file = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pout = new PrintWriter(System.out);
        
        int N = nextInt();
    loop:
        for(int x = 0;x<N;x++)
        {
            int a = position.indexOf(next().charAt(0));
            int b = nextInt()-1;
            int c = position.indexOf(next().charAt(0));
            int d = nextInt()-1;
            
            if((a+b)%2 != (c+d)%2)
            {
                System.out.println("Impossible");
            }else {
                if(a == c && b == d)
                {
                    System.out.println(0 +" "+position.charAt(a)+" "+(b+1));
                }else if(canMove(a,b,c,d))
                {
                    System.out.println(1 + " " + position.charAt(a)+" "+(b+1)+" "+position.charAt(c)+" "+(d+1));
                }else {
                    for(int i = 0;i<8;i++)
                    {
                        for(int j = 0;j<8;j++)
                        {
                            if(canMove(a,b,i,j) && canMove(i,j,c,d))
                            {
                                System.out.println(2+" "+position.charAt(a)+" "+(b+1)+" "+position.charAt(i)+" "+(j+1)+" "+position.charAt(c)+" "+(d+1));
                                continue loop;
                            }
                        }
                    }
                }
            }
        }
        
        
        
        
        
        pout.flush();
        pout.close();
    }
    
    public boolean canMove(int a, int b, int c, int d)
    {
        return a-b == c-d || a+b == c+d;
    }

    //don't worry about this, just a helper method
    public void newst()
    {
        try {
            st = new StringTokenizer(file.readLine());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    //consumes the entire next line of input
    public String readLine() throws IOException
    {
        return file.readLine();
    }
    
    //get's the next word of input
    public String next()
    {
        if(st == null || !st.hasMoreTokens())
            newst();
        return st.nextToken();
    }
    
    //tries to parse the next piece of input as an int
    public int nextInt()
    {
        if(st == null || !st.hasMoreTokens())
            newst();
        return Integer.parseInt(st.nextToken());
    }
    
    //tries to parse the next piece of input as a long
    public long nextLong()
    {
        if(st == null || !st.hasMoreTokens())
            newst();
        return Long.parseLong(st.nextToken());
    }
    
}