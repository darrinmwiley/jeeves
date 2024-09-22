/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/deliveryperson
TAGS: dijkstra, dp
EXPLANATION:
your position is completely encoded by (X,Y,Facing).

max distance between any two successive deliveries is 10 in both x and y, 
hence there are (4)^2(10*2+1)^2 distinct trips between two deliveries
(4 ways to begin your trip facing)(10*2+1 total delta x)*(10*2+1 total delta y)*(4 ways to end your trip facing)
									^ you can go backwards up to 10, stay still, or go forwards up to 10
									
it is also possible that a route could go just past the delivery zone in order to make 3 turns in a row, 
in the case where one turn is much more expensive than the other. Hence relevant positions are padded
by one in each direction, making the number of relevant positions (4)^2(10*2+3)^2.

We can use dijkstra to calculate the cost of every trip of size (deltax, deltay) starting facing direction F and ending facing direction F`

Next we will use dp to calculate the overall answer. 

dp[i][j] = the minimum cost of delivering the first i packages ending facing direction j

dp[i][j] = min (dp[i-1][j`] + cost of going from location i-1 facing j` to location i facing j)

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
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.StringTokenizer;
 
public class deliveryperson {
    
    //this is used for actual solution output. It is very fast but will not show up on the console until the run() method terminates (or until you call pout.flush()).
    PrintWriter pout;
    
    //this is used for timing your code
    long startTimeMillis;
    long benchmark;
    
    //set this to false to remove all debug and timing output for submission.
    boolean DEBUG_FLAG = true;
    
    int[][][][] cost;
    boolean[][][][] vis;
    
    int N;
    int B,S,R,L;
    
    int BIG = Integer.MAX_VALUE/4;
    int WID = 10;
    
    //this is just the entry point of your program. 
    //it will instantiate an instance of your solution class, set it's relevent variables, and then call its run() method to do the solving.
    //this also prints all output in pout's buffer for you after run() is complete.
    public static void main(String[] args) throws Exception
    {
        long entryTime = System.currentTimeMillis();
        deliveryperson t = new deliveryperson();
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
        B = file.nextInt();
        S = file.nextInt();
        R = file.nextInt();
        L = file.nextInt();
        N = file.nextInt();
        cost = new int[4][WID*2+3][WID*2+3][4];//original facing,x, y, end facing
        for(int i = 0;i<4;i++)
        {
            for(int j = 0;j<WID*2+3;j++)
            {
                for(int k = 0;k<WID*2+3;k++)
                {
                    for(int l = 0;l<4;l++)
                    {
                        cost[i][j][k][l] = BIG;
                    }
                }
            }
        }
        vis = new boolean[4][WID*2+3][WID*2+3][4];
        for(int i = 0;i<4;i++)
            d(i);
        // WID + 1 + negative y change, WID + 1 + x change
        int[] x = new int[N+1];
        int[] y = new int[N+1];
        x[0] = 0;
        y[0] = 0;
        for(int i = 0;i<N;i++)
        {
            x[i+1] = file.nextInt();
            y[i+1] = file.nextInt();
        }
        int[][] dp = new int[N+1][4];
        for(int i = 1;i<dp.length;i++)
        {
            Arrays.fill(dp[i], BIG);
        }
        for(int i = 1;i<dp.length;i++)
        {
            int deltax = x[i] - x[i-1];
            int deltay = y[i] - y[i-1];
            for(int j = 0;j<4;j++)
            {
                int min = BIG;
                for(int k = 0;k<4;k++)
                {
                    dp[i][j] = Math.min(dp[i][j], dp[i-1][k] + cost[k][WID + 1 - deltay][WID + 1 + deltax][j] - B);
                }
            }
        }

        System.out.println(Math.min(Math.min(dp[dp.length - 1][0],dp[dp.length - 1][1]),Math.min(dp[dp.length - 1][2], dp[dp.length - 1][3])));
    }
    
    int[][] d = new int[][] {{-1,0,1,0},{0,1,0,-1}};
    
    //1 = up
    //2 = right
    //3 = down
    //4 = left
    //right turn will add one to your facing, left turn will subtract one
    //start with cost of B 1 away from origin
    public void d(int f)
    {
         Queue<state> que = new PriorityQueue<state>();
         state start = new state(WID+1,WID+1,f, B);
         que.add(start);
         while(!que.isEmpty())
         {
             state st = que.poll();
             if(!vis[f][st.r][st.c][st.f] && cost[f][st.r][st.c][st.f] > st.cost)
             {
                 vis[f][st.r][st.c][st.f] = true;
                 cost[f][st.r][st.c][st.f] = st.cost;
                 state forward = new state(st.r+d[0][st.f], st.c+d[1][st.f], st.f, st.cost + S + B);
                 state right = new state(st.r+d[0][(st.f+1)%4], st.c+d[1][(st.f+1)%4], (st.f+1)%4, st.cost + R + B);
                 state left = new state(st.r+d[0][(st.f+3)%4], st.c+d[1][(st.f+3)%4], (st.f+3)%4, st.cost + L + B);
                 for(state s: new state[] {forward, right, left})
                 {
                     if(val(s.r,s.c) && !vis[f][s.r][s.c][s.f] && cost[f][s.r][s.c][s.f] > s.cost)
                     {
                         que.add(s);
                     }
                 }
             }
         }
    }
    
    public boolean val(int r, int c)
    {
        return Math.min(r,c) >=0 && Math.max(r,c) < WID*2+3;
    }
    
    private class state implements Comparable<state>{
        
        int r,c,f,cost;
        
        public state(int r, int c, int f, int cs)
        {
            this.r = r;
            this.c = c;
            this.f = f;
            this.cost = cs;
        }
        
        public int compareTo(state s)
        {
            return Integer.compare(cost, s.cost);
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
