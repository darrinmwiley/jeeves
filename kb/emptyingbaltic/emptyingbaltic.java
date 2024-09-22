/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/emptyingbaltic
TAGS: graph, dijkstra
EXPLANATION:
the amount of water left in a square after draining is equal to the lowest highest depth on any path from the square to the drain.
use a process similar to dijkstra's algorithm to find this lowest highest value for each location (do this from drain outward to only have to perform one dijkstra)
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.StringTokenizer;
 
public class emptyingbaltic {
    
    StringTokenizer st;
    BufferedReader file;
    
    public static void main(String[] args) throws Exception
    {
        new emptyingbaltic().run();
    }
    
    int[][] d = new int[][] {{-1,-1,-1,0,0,1,1,1},{-1,0,1,-1,1,-1,0,1}};
    
    boolean[][] vis;
    int[][] map;
    int[][] deepest;
    
    public void run() throws Exception
    {
        
        //this is fast IO - faster than Scanner/System.out.println
        file = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pout = new PrintWriter(System.out);
        
        //ASNWER WILLB E LONG
        
        int R = nextInt();
        int C = nextInt();
        
        map = new int[R][C];
        vis = new boolean[R][C];
        deepest = new int[R][C];
        
        for(int i = 0;i<R;i++)
        {
            for(int j = 0;j<C;j++)
            {
                map[i][j] = nextInt();
            }
        }
        
        int startR = nextInt()-1;
        int startC = nextInt()-1;
        int startH = map[startR][startC];
        
        Queue<state> que = new PriorityQueue<state>();
        
        que.add(new state(startR, startC, map[startR][startC]));
        
        while(!que.isEmpty())
        {
            state curr = que.poll();
            int r = curr.r;
            int c = curr.c;
            int h = curr.height;
            vis[r][c] = true;
            deepest[r][c] = h;
            for(int i = 0;i<8;i++)
            {
                int rr = r+d[0][i];
                int cc = c+d[1][i];
                if(valid(rr,cc) && map[rr][cc] < 0 && !vis[rr][cc])
                {
                    vis[rr][cc] = true;
                    que.add(new state(rr,cc,Math.max(h, map[rr][cc])));
                }
            }
        }
        
        long ans = 0;
        
        for(int i = 0;i<R;i++)
        {
            for(int j = 0;j<C;j++)
            {
                ans += -deepest[i][j];
            }
        }
        
        pout.println(ans);
        pout.flush();
        pout.close();
    }
    
    public boolean valid(int r, int c)
    {
        return Math.min(r,c) >= 0 && r < map.length && c < map[r].length;
    }
    
    private class state implements Comparable<state>{
        
        int r;
        int c;
        int height;
        
        public state(int r, int c, int h)
        {
            this.r = r;
            this.c =c ;
            this.height = h;
        }

        @Override
        public int compareTo(state o) {
            return height - o.height;
        }
        
        
        
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