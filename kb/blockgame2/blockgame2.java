/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/blockgame2
TAGS: game, memo, dp, math
EXPLANATION:

for the case (a, b) where W.L.O.G a <= b, you know at some point the state of the problem must pass through (b%a, a).

if (b%a, a) is a forced move (the case that b = a+b%a), then there is no choice and you must make that move

Otherwise, you can choose to either take that game state yourself, or give it to your opponent.

(a, b%a+a) = take state yourself, because the opponent is forced to give it to you
(b%a, a) = give state to your opponent

Under the same logic of Euclid's GCD algorithm, this will give a logarithmic number of subproblems to solve. I memoized to be safe.
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.StringTokenizer;
 
public class blockgame2 {
    
    StringTokenizer st;
    BufferedReader file;
    PrintWriter pout;
    HashMap<String, Boolean> map;
    
    
    
    //1) force enemy to go below next
    //2) go below next yourself
    
    public static void main(String[] args) throws Exception
    {
        new blockgame2().run();
    }   
    
    int r,c;
    
    public void run() throws Exception
    {
        file = new BufferedReader(new InputStreamReader(System.in));
        pout = new PrintWriter(System.out);
        map = new HashMap<String,Boolean>();
        long a = nextLong();
        long b = nextLong();
        boolean win = rec(Math.min(a, b), Math.max(a, b));
        if(win)
        {
            pout.println("win");
        }else {
            pout.println("lose");
        }
        pout.flush();
        pout.close();
    }
    
    //a smaller, b larger
    public boolean rec(long a, long b)
    {
            String str = a+" "+b;
            if(map.containsKey(str))
            {
                return map.get(str);
            }
            if(b%a == 0)
            {
                map.put(str, true);
                return true;
            }
            long mod = b%a;
            if(b-a == mod)
            {
                boolean ret = !rec(b-a,a);
                map.put(str, ret);
                return ret;
            }else {
                boolean ret = !rec(mod, a) || !rec(a, mod+a);
                map.put(str, ret);
                return ret;
            }
    }
    
    public boolean val(int rr, int cc)
    {
             return Math.min(rr,cc) >=0 && rr < r && cc < c;
    }
    
    private class state implements Comparable<state>{
        
            int r, c, cost;
            
            public state(int r, int c, int cost)
            {
                this.r =r ;
                this.c =c ;
                this.cost =cost;
            }

            @Override
            public int compareTo(state o) {
                return Integer.compare(cost, o.cost);
            }
        
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