/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/fire2
TAGS: bfs
EXPLANATION:
first multisource bfs out from each fire to determine the time at which each square catches on fire.
next, bfs from the starting position. A square is valid iff the time to reach it is less than the fire's time.
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;
 
public class fire2 {
    
    StringTokenizer st;
    BufferedReader file;
    
    int R,C;
    int[][] fire;
    char[][] chars;
    boolean[][] vis, visFire;
    int[][] d = new int[][] {{1,0,-1,0},{0,1,0,-1}};
    
    public static void main(String[] args) throws Exception
    {
        new fire2().run();
    }   
    
    public void run() throws Exception
    {
        //this is fast IO - faster than Scanner/System.out.println
        file = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pout = new PrintWriter(System.out);
        
        int zz = nextInt();
       loop:
        for(int z = 0;z<zz;z++)
        {
            C = nextInt();
            R = nextInt();
            chars = new char[R][C];
            fire = new int[R][C];
            visFire = new boolean[R][C];
            vis = new boolean[R][C];
            
            for(int i = 0;i<fire.length;i++)
                Arrays.fill(fire[i], 2000000);
            
            for(int i = 0;i<R;i++)
                chars[i] = next().toCharArray();
            
            Queue<Integer> que = new LinkedList<Integer>();
            
            for(int i = 0;i<R;i++)
            {
                for(int j = 0;j<C;j++)
                {
                    if(chars[i][j] == '*')
                    {
                        que.add(i);
                        que.add(j);
                        que.add(0);
                    }
                }
            }
            
            while(!que.isEmpty())
            {
                int r = que.poll();
                int c = que.poll();
                int cost = que.poll();
                if(!visFire[r][c])
                {
                    visFire[r][c] = true;
                    fire[r][c] = cost;
                    for(int i = 0;i<4;i++)
                    {
                        int rr = r+d[0][i];
                        int cc = c+d[1][i];
                        if(val(rr,cc))
                        {
                            que.add(rr);
                            que.add(cc);
                            que.add(cost + 1);
                        }
                    }
                }
            }
            
            for(int i = 0;i<R;i++)
            {
                for(int j = 0;j<C;j++)
                {
                    if(chars[i][j] == '@')
                    {
                        que.add(i);
                        que.add(j);
                        que.add(0);
                    }
                }
            }
            
            while(!que.isEmpty())
            {
                int r = que.poll();
                int c = que.poll();
                int cost = que.poll();
                if(r == 0 || c == 0 || r == R - 1 || c == C - 1)
                {
                    System.out.println(cost + 1);
                    continue loop;
                }
                if(!vis[r][c])
                {
                    vis[r][c] = true;
                    for(int i = 0;i<4;i++)
                    {
                        int rr = r+d[0][i];
                        int cc = c+d[1][i];
                        if(val(rr,cc) && fire[rr][cc] > cost + 1)
                        {
                            que.add(rr);
                            que.add(cc);
                            que.add(cost + 1);
                        }
                    }
                }
            }
            
            System.out.println("IMPOSSIBLE");
        }
        
        
        
        pout.flush();
        pout.close();
    }
    
    boolean val(int r, int c)
    {
        return Math.min(r,c) >= 0 && r < R && c < C && chars[r][c] != '#';
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