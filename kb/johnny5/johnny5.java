/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/johnny5
TAGS: BFS
EXPLANATION:
there are a certain number of interesting locations*times. All others we can disregard.

Interesting locations*time pairs are 

1) the beginning spot at time 0
2) all oil can spots at the time oil cans appear
3) all spaces adjacent to oil can spots at the time oil cans appear

each interesting location*time has a certain energy profit and a certain point profit.

your complete state is encompassed by (interesting location*time id, energy left, profit)

bfs over the entire state space, keeping track of the largest profit achieved for each (location*time, energy) tuple encountered.
use pruning to eliminate suboptimal states.

The answer is the maximum profit of all states.

There are at most 500 interesting location*times, and any energy over ~100 is wasted (there are only 100 timesteps),
 so we only consider energy values of up to 100.
 
hence state space is (500*100)
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
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;
 
public class johnny5 {
    
    //this is used for actual solution output. It is very fast but will not show up on the console until the run() method terminates (or until you call pout.flush()).
    PrintWriter pout;
    
    //this is used for timing your code
    long startTimeMillis;
    long benchmark;
    
    //set this to false to remove all debug and timing output for submission.
    boolean DEBUG_FLAG = true;
    
    node[] nodes;
    
    int N;
    
    int BIG = Integer.MAX_VALUE/4;
    
    //this is just the entry point of your program. 
    //it will instantiate an instance of your solution class, set it's relevent variables, and then call its run() method to do the solving.
    //this also prints all output in pout's buffer for you after run() is complete.
    public static void main(String[] args) throws Exception
    {
        long entryTime = System.currentTimeMillis();
        johnny5 t = new johnny5();
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
        N = file.nextInt();
        int E = file.nextInt();
        int Sr = file.nextInt();
        int Sc = file.nextInt();
        int C = file.nextInt();
        int[] canR = new int[C];
        int[] canC = new int[C];
        int[] canT = new int[C];
        for(int i = 0;i<C;i++)
        {
            canR[i] = file.nextInt();
            canC[i] = file.nextInt();
            canT[i] = file.nextInt();
        }
        HashSet<String> locationTriples = new HashSet<String>();
        ArrayList<Integer> importantR = new ArrayList<Integer>();
        ArrayList<Integer> importantC = new ArrayList<Integer>();
        ArrayList<Integer> importantT = new ArrayList<Integer>();
        importantR.add(Sr);
        importantC.add(Sc);
        importantT.add(0);
        int[][] d = new int[][] {{-1,0,1,0,0},{0,1,0,-1,0}};
        for(int i = 0;i<C;i++)
        {
            for(int k = 0;k<5;k++)
            {
                int rr = canR[i] + d[0][k];
                int cc = canC[i] + d[1][k];
                int T = canT[i];
                if(valid(rr,cc))
                {
                    boolean add = locationTriples.add(rr+" "+cc+" "+T);
                    if(add)
                    {
                        importantR.add(rr);
                        importantC.add(cc);
                        importantT.add(T);
                    }
                }
            }
        }
        int[] locationEnergyProfit = new int[importantR.size()];
        int[] locationProfit = new int[importantR.size()];
        int[][] adj = new int[][] {{1,0,-1,0},{0,1,0,-1}};
        for(int i = 0;i<importantR.size();i++)
        {
            int r = importantR.get(i);
            int c = importantC.get(i);
            int t = importantT.get(i);
            for(int k = 0;k<C;k++)
            {
                int compr = canR[k];
                int compc = canC[k];
                int compt= canT[k];
                if(compt == t && compr == r && compc == c)
                {
                    locationProfit[i]++;
                }
                if(compt == t && Math.abs(compc - c) + Math.abs(compr - r) == 1)
                {
                    locationEnergyProfit[i]++;
                }
            }
        }
        int[][] best = new int[importantR.size()][102];
        for(int[] in:best)
                Arrays.fill(in, -1);
        state begin = new state(0,0,E,0);
        best[0][E] = 0;
        Queue<state> que = new LinkedList<state>();
        que.add(begin);
        while(!que.isEmpty())
        {
            state st = que.poll();
            int t = st.t;
            int l = st.l;
            int e = st.e;
            int p = st.p;
            int currR = importantR.get(l);
            int currC = importantC.get(l);
            for(int i = 0;i<importantR.size();i++)
            {
                int nextR = importantR.get(i);
                int nextC = importantC.get(i);
                int nextT = importantT.get(i);
                int dist = dist(currR, currC, nextR, nextC);
                if(Math.min(nextT - t, e) >= dist && t != nextT)
                {
                    state next = new state(nextT, i, e - dist + locationEnergyProfit[i], p + locationProfit[i]);
                    if(next.p > best[next.l][Math.min(next.e, 101)])
                    {
                        best[next.l][Math.min(next.e, 101)] = next.p;
                        que.add(next);
                    }
                }
            }
        }
        int ans = 0;
        for(int[] in: best)
        {
            for(int x: in)
            {
                ans = Math.max(ans, x); 
            }
        }
        System.out.println(ans);
    }
    
    public int dist(int r1, int c1, int r2, int c2)
    {
        return Math.abs(r1 - r2) + Math.abs(c1 - c2);
    }
    
    /*private class importantLocation implements Comparable<>{
        
        int r, c, T, energyProfit, profit;
        
        public importantLocation(int r, int c, int t, int ep, int p)
        {
            this.r = r;
            this.c = c;
            this.T = t;
            this.energyProfit = ep;
            this.profit = p;
        }
        
    }*/
    
    private class state{
        
        int t, l, e, p;
        
        public state(int t, int l, int e, int p)
        {
            this.t =t ;
            this.l = l;
            this.e = e;
            this.p = p;
        }
        
    }
    
    public boolean valid(int r, int c)
    {
        return Math.min(r,c) > -1 && Math.max(r,c) < N;
    }
    
    private class node{
        
        ArrayList<Integer> con;
        int topScore = 0;
        int r;//r location
        int c;//c location
        int e;//energy
        int ep;//energy profit
        int p;//profit benefit
        
        public node(int r, int c, int e,int ep, int p)
        {
            this.r = r;
            this.c = c;
            this.e = e;
            this.ep = ep;
            
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