/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/mallmania
TAGS: bfs
EXPLANATION:
all vertices of mall one are sources, and all vertices of mall two are are destinations. Run a multisource BFS and terminate when you find the first sink.
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
 
public class mallmania {
    
    StringTokenizer st;
    BufferedReader file;
    
    int[][] d = new int[][] {{1,0,-1,0},{0,1,0,-1}};
    boolean[][] vis = new boolean[2001][2001];
    
    public static void main(String[] args) throws Exception
    {
        new mallmania().run();
    }   
    
    public void run() throws Exception
    {
        //this is fast IO - faster than Scanner/System.out.println
        file = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pout = new PrintWriter(System.out);
        
        
        while(true)
        {
        	boolean[][] mall = new boolean[2001][2001];
        	
        	int N = nextInt();
            if(N == 0)
                break;
            int[] X1 = new int[N];
            int[] Y1 = new int[N];
            
            for(int i = 0;i<N;i++)
            {
                X1[i] = nextInt();
                Y1[i] = nextInt();
            }
            
            int M = nextInt();
            int[] X2 = new int[M];
            int[] Y2 = new int[M];
            
            for(int i = 0;i<M;i++)
            {
                X2[i] = nextInt();
                Y2[i] = nextInt();
                mall[X2[i]][Y2[i]] = true;
            }   
            
            for(int j = 0;j<2001;j++)
            {
                Arrays.fill(vis[j], false);
            }
            
            Queue<state> que = new LinkedList<state>();
            
            for(int i = 0;i<N;i++) {
            	que.add(new state(X1[i], Y1[i], 0));
            	vis[X1[i]][Y1[i]] = true;
            }
            
            int ans = -1;
            
            while(!que.isEmpty())
            {
            	state st = que.poll();
            	int rr = st.r;
            	int cc = st.c;
            	int cost = st.cost;
                if(mall[rr][cc])
                {
                	ans = cost;
                	break;
                }
                vis[rr][cc] = true;
                for(int i = 0;i<4;i++)
                {
                    int newr = rr+d[0][i];
                    int newc = cc+d[1][i];
                    if(val(newr, newc) && !vis[newr][newc])
                    {
                        que.add(new state(newr, newc, cost+1));
                        vis[newr][newc] = true;
                    }
                }
            }
            
            pout.println(ans);

        }
        
 
        pout.flush();
        pout.close();
    } 
    
    public boolean val(int rr, int cc)
    {
        return Math.min(rr,cc) >= 0 && rr<2001 && cc<2001;
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