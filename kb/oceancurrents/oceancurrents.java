/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/oceancurrents
TAGS: dijkstra
EXPLANATION:
run repeated dijkstra for all n trips.
You can use directional matrices to make movement and cost calculation much easier.
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.StringTokenizer;
 
public class oceancurrents {
    
    StringTokenizer st;
    BufferedReader file;
    
    int[][] d = new int[][] {{-1,-1,0,1,1,1,0,-1},{0,1,1,1,0,-1,-1,-1}};
    boolean[][] vis;
    int[][] fp;
    
    int r;
    int c;
    
    long modulus = 1000000007;
    
    public static void main(String[] args) throws Exception
    {
        new oceancurrents().run();
    }   
    
    public void run() throws Exception
    {
        //this is fast IO - faster than Scanner/System.out.println
        file = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pout = new PrintWriter(System.out);
        
        r = nextInt();
        c = nextInt();
        
        int[][] ints = new int[r][c];
        
        for(int i = 0;i<ints.length;i++)
        {
            char[] str = next().toCharArray();
            for(int j = 0;j<str.length;j++)
            {
                ints[i][j] = str[j] - '0';
            }
        }
        
        int M = nextInt();
        
        vis = new boolean[r][r];
        fp = new int[r][c];
        
        for(int x = 0;x<M;x++)
        {
            int r1 = nextInt() - 1;
            int c1 = nextInt() - 1;
            int r2 = nextInt() - 1;
            int c2 = nextInt() - 1;
            for(int j = 0;j<r;j++)
            {
                Arrays.fill(vis[j], false);
                Arrays.fill(fp[j],Integer.MAX_VALUE/4);
            }
            
            PriorityQueue<state> que = new PriorityQueue<state>();
            state initial = new state(r1, c1, 0);
            que.add(initial);
            
            while(!que.isEmpty())
            {
                state curr = que.poll();
                //System.out.println(curr.r+1+" "+(curr.c+1)+" "+curr.cost);
                int rr = curr.r;
                int cc = curr.c;
                if(vis[rr][cc])
                {
                    continue;
                }
                vis[rr][cc] = true;
                fp[rr][cc] = Math.min(fp[rr][cc],curr.cost);
                for(int i = 0;i<8;i++)
                {
                    int newr = rr+d[0][i];
                    int newc = cc+d[1][i];
                    int newcost = curr.cost;
                    if(i != ints[rr][cc])
                        newcost++;
                    if(val(newr, newc) && newcost < fp[newr][newc])
                    {
                        fp[newr][newc] = newcost;
                        state next = new state(newr, newc, newcost);
                        que.add(next);
                    }
                }
            }
            
            System.out.println(fp[r2][c2]);
            
        }
 
        pout.flush();
        pout.close();
    } 
    
    public boolean val(int rr, int cc)
    {
        return Math.min(rr,cc) >= 0 && rr<r && cc<c;
    }
    
    private class state implements Comparable<state>{

        int r;
        int c;
        int cost;
        
        public state(int r, int c, int cc)
        {
            this.r = r;
            this.c = c;
            this.cost = cc;
        }
        
        public int compareTo(state s)
        {
            return Integer.compare(cost,  s.cost);
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