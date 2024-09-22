/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/muddyhike
TAGS: bellman ford
EXPLANATION:

END ANNOTATION
/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/muddyhike
TAGS: dijkstra
EXPLANATION:
standard dijkstra's algorithm
instead of adding to successor state cost, you set cost to the maximum of currentCost and next depth.
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;
 
public class muddyhike {
    
    StringTokenizer st;
    BufferedReader file;
    PrintWriter pout;
    
    public static void main(String[] args) throws Exception
    {
        new muddyhike().run();
    }   
    
    int r,c;
    
    public void run() throws Exception
    {
        file = new BufferedReader(new InputStreamReader(System.in));
        pout = new PrintWriter(System.out);
        r = nextInt();
        c = nextInt();
        int[][]ints = new int[r][c];
        int[][] fp = new int[r][c];
        boolean[][] vis = new boolean[r][c];
        
        for(int i = 0;i<r;i++)
        {
                Arrays.fill(fp[i], Integer.MAX_VALUE);
        }
        
        for(int i = 0;i<r;i++)
        {
                for(int j = 0;j<c;j++)
                {
                    ints[i][j] = nextInt();
                }
        }
        
        PriorityQueue<state> que = new PriorityQueue<state>();
        
        for(int i = 0;i<ints.length;i++)
        {
                state st = new state(i,0,ints[i][0]);
                que.add(st);
        }
        
        int[][] d = new int[][] {{-1,0,1,0},{0,1,0,-1}};
        
        while(!que.isEmpty())
        {
                state st = que.poll();
                int rr = st.r;
                int cc = st.c;
                //System.out.println(rr+" "+cc+" "+st.cost);
                if(cc == c-1)
                {
                    System.out.println(st.cost);
                    return;
                }
                int cost = st.cost;
                if(vis[rr][cc])
                    continue;
                vis[rr][cc] = true;
                fp[rr][cc] = cost;
                for(int i = 0;i<4;i++)
                {
                    int nextR = rr+d[0][i];
                    int nextC = cc+d[1][i];
                    if(val(nextR, nextC))
                    {
                        int nextCost = Math.max(ints[nextR][nextC], cost);
                        if(fp[nextR][nextC] > nextCost)
                        {
                            state next = new state(nextR, nextC, nextCost);
                            fp[nextR][nextC] = nextCost;
                            que.add(next);
                        }
                    }
                }
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