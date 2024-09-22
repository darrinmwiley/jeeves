/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/linije
TAGS: flow, matching
EXPLANATION:
We can view this problem as a bipartite graph where vertical lines are on one side, and horizontal lines on the other.

We will connect two nodes if one line can be played directly after another. 
This is the case if two lines are of opposite types and share a point

Drawing a line is equivalent to removing a node from the graph, and the first person to not be able to remove another node loses.

If there is a perfect matching between nodes, Slavko can always remove match(x) right after Mirko removes X, which would guarantee Slavko taking the last node.

Otherwise, Mirko can start from an unmatched node. 
The node Slavko removes after Mirko is guaranteed to have a match. If it didn't, the node Mirko removed would be able to match with it.
If Mirko starts from an unmatched node, he can then always remove the match of any node Slavko removes afterwards. 
Hence Mirko will always have a move left and Slavko must lose

This shows that an optimal strategy exists for Slavko when a perfect matching exists, and an optimal strategy exists for Mirko otherwise.

We can implement the matching algorithm with max flow, as the runtime is (V+E)F, where F is the total flow. 
Because there are at most 500 nodes on each side of the bipartite graph, the max flow is at most 500. 

Hence complexity =~ (10,000)(500) = 5,000,000 operations
END ANNOTATION
*/
/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/hauntedgraveyard
TAGS: bellman ford
EXPLANATION:

END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;
 
public class linije {
    
    StringTokenizer st;
    BufferedReader file;
    PrintWriter pout;
    HashMap<String, Boolean> map;
    
    node[] nodes;
    int[] p;
    boolean[] vis;
    
    int numNodes = 501;
    int networkSize = numNodes*2 + 2;
    
    //1) force enemy to go below next
    //2) go below next yourself
    
    public static void main(String[] args) throws Exception
    {
        new linije().run();
    }   
    
    int[][] res;
    
    public void run() throws Exception
    {
        file = new BufferedReader(new InputStreamReader(System.in));
        pout = new PrintWriter(System.out);
        boolean[] lineX = new boolean[numNodes];
        boolean[] lineY = new boolean[numNodes];
        //source, lineX, lineY, sink
        int N = nextInt();
        int[] ptX = new int[N];
        int[] ptY = new int[N];
        
        boolean[][] con = new boolean[numNodes][numNodes];
        for(int i = 0;i<N;i++)
        {
                ptX[i] = nextInt();
                ptY[i] = nextInt();
                lineX[ptX[i]] = true;
                lineY[ptY[i]] = true;
                con[ptX[i]][ptY[i]] = true;
        }
        res = new int[networkSize][networkSize];
        nodes = new node[networkSize];
        for(int i = 0;i<nodes.length;i++)
        {
                nodes[i] = new node(i);
        }
        for(int i = 0;i<numNodes;i++)
        {
                con(0, i+1);
                con(502+i,nodes.length - 1);
        }
        for(int i = 0;i<numNodes;i++)
        {
                for(int j = 0;j<numNodes;j++)
                {
                    if(con[i][j])
                    {
                        con(i+1, numNodes+j);
                    }
                }
        }
        int flow = 0;
        while(aug())
        {
                flow++;
        }
        int sumX = 0;
        int sumY = 0;
        for(int i = 0;i<lineX.length;i++)
        {
                if(lineX[i]) {
                    sumX++;
                }
                if(lineY[i]) {
                    sumY++;
                }
        }
        if(sumX == sumY && flow == sumX)
        {
                pout.println("Slavko");
        }else {
                pout.println("Mirko");
        }
        pout.flush();
        pout.close();
    }
    
    public boolean aug()
    {
            vis = new boolean[networkSize];
            p = new int[networkSize];
            Arrays.fill(p, -1);
            Queue<Integer> que = new LinkedList<Integer>();
            que.add(0);
            while(!que.isEmpty())
            {
                int x = que.poll();
                vis[x] = true;
                if(x == networkSize - 1)
                {
                    traceback();
                    return true;
                }
                node n = nodes[x];
                for(int y: n.con)
                {
                    if(!vis[y] && res[x][y] > 0)
                    {
                        p[y] = x;
                        vis[y] = true;
                        que.add(y);
                    }
                }
            }
            return false;
    }
    
    public void traceback()
    {
            int curr = networkSize - 1;
            while(p[curr] != -1)
            {
                res[p[curr]][curr]--;
                res[curr][p[curr]]++;
                curr = p[curr];
            }
    }
    
    public void con(int a, int b)
    {
            nodes[a].con.add(b);
            nodes[b].con.add(a);
            res[a][b] = 1;
    }
    
    private class node{
        
            public ArrayList<Integer> con;
            int id;
            
            public node(int id)
            {
                con = new ArrayList<Integer>();
                this.id = id;
            }
        
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