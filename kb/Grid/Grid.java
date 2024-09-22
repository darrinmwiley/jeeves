/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/grid
TAGS: bfs
EXPLANATION:
standard bfs where successor states are a function of the value at your current location
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;
 
public class Grid {
    
    StringTokenizer st;
    BufferedReader file;
    
    int[][] d = new int[][] {{1,0,-1,0},{0,1,0,-1}};
    int R,C;
    
    public static void main(String[] args) throws Exception
    {
        new Grid().run();
    }   
    
    public void run() throws Exception
    {
        //this is fast IO - faster than Scanner/System.out.println
        file = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pout = new PrintWriter(System.out);
        
        R = nextInt();
        C = nextInt();
        
        int[][] ints = new int[R][C];
        boolean[][] vis = new boolean[R][C];
        for(int i = 0;i<R;i++)
        {
            char[] chars = next().toCharArray();
            for(int j = 0;j<C;j++)
            {
                ints[i][j] = chars[j] - '0';
            }
        }
        
        Queue<Integer> que = new LinkedList<Integer>();
        que.add(0);
        que.add(0);
        que.add(0);
        
        while(!que.isEmpty())
        {
            int rr = que.poll();
            int cc = que.poll();
            int cost = que.poll();
            if(val(rr,cc))
            {
                if(vis[rr][cc])
                    continue;
                vis[rr][cc] = true;
                int jump = ints[rr][cc];
                if(rr == R-1 && cc == C-1)
                {
                    pout.println(cost);
                    pout.flush();
                    return;
                }
                for(int i = 0;i<4;i++)
                {
                    que.add(rr+d[0][i]*jump);
                    que.add(cc+d[1][i]*jump);
                    que.add(cost+1);
                }
            }
        }
        pout.println(-1);
        
        pout.flush();
        pout.close();
    }
    
    boolean val(int r, int c)
    {
        return Math.min(r,c) >= 0 && r < R && c < C;
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