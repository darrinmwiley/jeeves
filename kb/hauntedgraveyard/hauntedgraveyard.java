/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/hauntedgraveyard
TAGS: bellman ford
EXPLANATION:
bellman ford with a few tricky edge cases

1) if one portal leaves you in a new portal space, you must take that immediately. This can be accomplished by not creating edges outgoing from any portal square
2) if you reach the exit, you exit immediately. This is accomplished by not creating edges coming out of the exit square
3) don't create edges going in or out of tombstone squares
4) do create edges between any two adjacent squares who don't satisfy any of the above conditions.
5) when doing bellman ford, make sure not to update a square if it's not reachable yet. This ensures that if an unreachable negative weight cycle exists you will still get the correct answer.

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
 
public class hauntedgraveyard {
    
    StringTokenizer st;
    BufferedReader file;
    
    boolean[] grave;
    boolean[] isEdge;
    boolean[][] EE;
    
    ArrayList<edge> edges;
    
    int R,C,G,E;
    
    int[][] d = new int[][] {{1,0,-1,0},{0,1,0,-1}};
    
    public static void main(String[] args) throws Exception
    {
        new hauntedgraveyard().run();
    }   
    
    public void run() throws Exception
    {
        file = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pout = new PrintWriter(System.out);
        
        while(true)
        {
            edges = new ArrayList<edge>();
            C = nextInt();
            R = nextInt();
            if(R==0 && C == 0)
                break;
            G = nextInt();
            EE = new boolean[R*C][R*C];
            grave = new boolean[R*C];
            isEdge = new boolean[R*C];
            for(int i = 0;i<G;i++)
            {
                int c = nextInt();
                int r = nextInt();
                grave[index(r,c)] = true;
            }
            E = nextInt();
            for(int i = 0;i<E;i++)
            {
                int x1 = nextInt();
                int y1 = nextInt();
                int x2 = nextInt();
                int y2 = nextInt();
                int t = nextInt();
                int i1 = index(y1, x1);
                int i2 = index(y2, x2);
                isEdge[i1] = true;
                con(i1, i2, t);
            }
            
            for(int r = 0;r<R;r++)
            {
                for(int c = 0;c<C;c++)
                {
                    int index1 = index(r,c);
                    if(grave[index1] || isEdge[index1] || index1 == R*C - 1)
                        continue;
                    for(int i = 0;i<d[0].length;i++)
                    {
                        int rr = r+d[0][i];
                        int cc = c+d[1][i];
                        int index2 = index(rr,cc);
                        if(val(rr,cc) && !grave[index2])
                        {
                            con(index1, index2,1);
                            if(!isEdge[index2] && index2 != R*C - 1)
                            	con(index2, index1,1);
                        }
                    }
                }
            }
            
            int[] distance = new int[R*C];
            Arrays.fill(distance, Integer.MAX_VALUE/4);
            distance[0] = 0;
            
            for(int i = 0;i<R*C;i++)
            {
                for(edge e: edges)
                {
                	if(e.u == distance.length - 1)
                		continue;
                    if(distance[e.u] != Integer.MAX_VALUE/4 && distance[e.u] + e.cost < distance[e.v])
                    {
                        distance[e.v] = distance[e.u] + e.cost;
                    }
                }
            }
            
            boolean loop = false;
            
            for(edge e:edges)
            {
                if(distance[e.u] != Integer.MAX_VALUE/4 && distance[e.u] + e.cost < distance[e.v])
                {
                    loop = true;
                }
            }
            
            int ans = distance[distance.length - 1];
            if(loop)
            {
                pout.println("Never");
            }else if(ans == Integer.MAX_VALUE / 4)
            {
                pout.println("Impossible");
            }else {
                pout.println(ans);
            }
        }
        pout.flush();
        pout.close();
    }
    
    public boolean val(int r, int c)
    {
        return Math.min(r,c) >=0 && r < R && c < C;
    }
    
    public void con(int a, int b, int c)
    {
    	if(!EE[a][b]) {
    		edges.add(new edge(a,b,c));
    		EE[a][b] = true;
    	}
    }
    
    public int index(int r, int c)
    {
        return C*r+c;
    }
    
    private class edge{
        
        int u, v, cost;
        
        public edge(int u, int v, int c)
        {
            this.u = u;
            this.v = v;
            this.cost = c;
        }
        
        public String toString()
        {
            return (u/R) + " "+ (u%R) +" "+ (v/R)+" "+(v%R);
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