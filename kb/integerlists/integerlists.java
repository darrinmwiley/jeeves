/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/integerlists
TAGS: list
EXPLANATION:
don't actually reverse the list, just maintain a flag to tell which end to remove from, and print them in the correct order depending on the flag after.
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Deque;
import java.util.LinkedList;
import java.util.StringTokenizer;
 
public class integerlists {
    
    StringTokenizer st;
    BufferedReader file;
    
    public static void main(String[] args) throws Exception
    {
        new integerlists().run();
    }   
    
    public void run() throws Exception
    {
        //this is fast IO - faster than Scanner/System.out.println
        file = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pout = new PrintWriter(System.out);
        
        int N = nextInt();
    loop:
        for(int i = 0;i<N;i++)
        {
            String str = next();
            int n = nextInt();
            String line = next().replaceAll("\\p{Punct}", " ").trim();
            StringTokenizer st2 = new StringTokenizer(line);
            Deque<Integer> list = new LinkedList<Integer>();
            for(int x = 0;x<n;x++)
            {
                list.add(Integer.parseInt(st2.nextToken()));
            }
            
            boolean rev = false;
            
            for(char ch:str.toCharArray())
            {
                if(ch == 'D')
                {
                    if(list.isEmpty())
                    {
                        pout.println("error");
                        continue loop;
                    }
                    if(rev)
                        list.removeLast();
                    else
                        list.removeFirst();
                }else {
                    rev = !rev;
                }
            }
            pout.print("[");
            if(rev) {
                while(!list.isEmpty())
                {
                    pout.print(list.removeLast());
                    if(!list.isEmpty())
                        pout.print(",");
                }
            }else {
                while(!list.isEmpty())
                {
                    pout.print(list.removeFirst());
                    if(!list.isEmpty())
                        pout.print(",");
                }
            }
            pout.println("]");
        }
        
        pout.flush();
        pout.close();
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